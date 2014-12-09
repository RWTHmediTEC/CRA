/*
 *  Copyright (C) 2010 - 2013 Leonid Kostrykin
 *
 *  Chair of Medical Engineering (mediTEC)
 *  RWTH Aachen University
 *  Pauwelsstr. 20
 *  52074 Aachen
 *  Germany
 *
 */

#include "glew.h"
#include "LinkedCameraImplementation.h"
#include "LinkedCameraImplementationDetails.h"
#include "Registration.h"
#include <QDir>
#include <QGLPixelBuffer>
#include <QDebug>

namespace CRA
{



// ----------------------------------------------------------------------------------
// toCMatrix
// ----------------------------------------------------------------------------------

static inline CMatrix toCMatrix3x3( const Transformation& t )
{
    CMatrix m( 3, 3 );

    m( 0, 0 ) = t.a11();
    m( 0, 1 ) = t.a12();
    m( 0, 2 ) = t.a13();

    m( 1, 0 ) = t.a21();
    m( 1, 1 ) = t.a22();
    m( 1, 2 ) = t.a23();

    m( 2, 0 ) = t.a31();
    m( 2, 1 ) = t.a32();
    m( 2, 2 ) = t.a33();

    return m;
}



// ----------------------------------------------------------------------------------
// getPixelBufferContext
// ----------------------------------------------------------------------------------

static QGLContext* getPixelBufferContext( QGLPixelBuffer* pbuffer )
{
    pbuffer->makeCurrent();
    const QGLContext* const context = QGLContext::currentContext();;
    return const_cast< QGLContext* >( context );
}



// ----------------------------------------------------------------------------------
// fetchCurrentMatrix
// ----------------------------------------------------------------------------------

static void fetchCurrentMatrix( Transformation& out, GLenum which_matrix )
{
    double matrix[ 16 ];

    glGetDoublev( which_matrix, matrix );

    for( int i = 0; i < 16; ++i )
    {
        out.getTransformationMatrix()( i % 4, i / 4 ) = matrix[ i ];
    }
}



// ----------------------------------------------------------------------------------
// fetchModelViewMatrix
// ----------------------------------------------------------------------------------

static void fetchModelViewMatrix( Transformation& out )
{
    fetchCurrentMatrix( out, GL_MODELVIEW_MATRIX );
}



// ----------------------------------------------------------------------------------
// fetchProjectionMatrix
// ----------------------------------------------------------------------------------

static void fetchProjectionMatrix( Transformation& out )
{
    fetchCurrentMatrix( out, GL_PROJECTION_MATRIX );
}



// ----------------------------------------------------------------------------------
// CRA_BREAK_FOR_DEBUG
// ----------------------------------------------------------------------------------

/** \brief
  * Causes a break point in debug mode, does nothing in release mode.
  *
  * \author Leonid Kostrykin
  * \date   5.3.13
  */
#ifdef _MSC_VER
#define CRA_BREAK_FOR_DEBUG __debugbreak();
#else
#define CRA_BREAK_FOR_DEBUG raise( SIGTRAP );
#endif



// ----------------------------------------------------------------------------------
// LinkedCameraImplementation :: Details
// ----------------------------------------------------------------------------------

LinkedCameraImplementation::Details::Details( LinkedCamera& self )
    : self ( self )
    , pbuffer( new QGLPixelBuffer( 8, 8, QGLFormat::defaultFormat() ) )
    , calibrationContext( getPixelBufferContext( pbuffer.get() ) )
    , registration( nullptr )
{
}


void LinkedCameraImplementation::Details::init
    ( const std::string& xrayEmptyTrf
    , const std::string& xrayEmptyCof
    , const std::string& transformationIni )
{
    int error = 0;

    error += std::abs( !trafo.LoadWorld2CArm( xrayEmptyTrf ) );
    error += std::abs(  trafo.LoadCal2CArm  ( xrayEmptyTrf ) );
    error += std::abs(  trafo.LoadCamCal    ( xrayEmptyCof ) );
    error += std::abs(  trafo.LoadCal2CArm  ( transformationIni ) );

    if( error != 0 )
    {
        CRA_BREAK_FOR_DEBUG;
        throw std::logic_error( "Attempt of loading camera calibration files failed." );
    }
}


LinkedCameraImplementation::Details::~Details()
{
}



// ----------------------------------------------------------------------------------
// LinkedCameraImplementation
// ----------------------------------------------------------------------------------

LinkedCameraImplementation::LinkedCameraImplementation( LinkedCamera& self )
    : pimpl( new Details( self ) )
{
    QString appPath = QDir::currentPath();

    const std::string xrayEmptyTrf = ( appPath + "\\XRayEmpty.trf" ).toStdString();
    const std::string xrayEmptyCof = ( appPath + "\\XRayEmpty.cof" ).toStdString();
    const std::string transformationIni = ( appPath + "\\transformation.ini" ).toStdString();

    pimpl->init( xrayEmptyTrf, xrayEmptyCof, transformationIni );
}


LinkedCameraImplementation::LinkedCameraImplementation
    ( LinkedCamera& self
    , const std::string& xrayEmptyTrf
    , const std::string& xrayEmptyCof
    , const std::string& transformationIni )

    : pimpl( new Details( self ) )
{
    pimpl->init( xrayEmptyTrf, xrayEmptyCof, transformationIni );
}


LinkedCameraImplementation::~LinkedCameraImplementation()
{
}


void LinkedCameraImplementation::compute( unsigned int shortestTargetSide )
{
    QGLContext* const originalContext = const_cast< QGLContext* >( QGLContext::currentContext() );
    pimpl->calibrationContext->makeCurrent();

    glViewport( 0, 0, shortestTargetSide, shortestTargetSide );

 // ----------------------------------------------------------------------------------

    const Transformation inverse_bearing = pimpl->physicalBearing.inverse();
    const CVector translation = CVector( inverse_bearing.a14(), inverse_bearing.a24(), inverse_bearing.a34() );
    const CMatrix rotation = toCMatrix3x3( inverse_bearing );
    pimpl->trafo.SetWorld2CArm( rotation, translation );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();

 // ----------------------------------------------------------------------------------

    const static double zoom = 1.;
    pimpl->trafo.GL_ApplyCameraCalibration( zoom * shortestTargetSide / 576.
        , 0, 0, shortestTargetSide, shortestTargetSide
        , -90. / 180. * PI, false );

    fetchModelViewMatrix( pimpl->camera );
    fetchProjectionMatrix( pimpl->projection );

 // ----------------------------------------------------------------------------------

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();

    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

 // ----------------------------------------------------------------------------------

    pimpl->calibrationContext->doneCurrent();
    if( originalContext )
    {
        originalContext->makeCurrent();
    }
}


void LinkedCameraImplementation::update( const Transformation& physical_bearing, const Registration& registration )
{
    pimpl->physicalBearing = physical_bearing;
    pimpl->registration = &registration;
}


bool LinkedCameraImplementation::hasRegistration() const
{
    return pimpl->registration != nullptr;
}


const Registration& LinkedCameraImplementation::registration() const
{
    if( pimpl->registration == nullptr )
    {
        CRA_BREAK_FOR_DEBUG;
        throw std::logic_error( "Assertion failed: registration not supplied to LinkedCamera yet." );
    }

    return *pimpl->registration;
}


const Transformation& LinkedCameraImplementation::cameraTransformation() const
{
    return pimpl->camera;
}


void LinkedCameraImplementation::setCameraTransformation( const Transformation& camera )
{
    pimpl->camera = camera;
}


const Transformation& LinkedCameraImplementation::projectionTransformation() const
{
    return pimpl->projection;
}


const Transformation& LinkedCameraImplementation::physicalBearing() const
{
    return pimpl->physicalBearing;
}



}  // namespace CRA
