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

#ifndef LINKEDCAMERA_H_2521354512
#define LINKEDCAMERA_H_2521354512

#include "VirtualElement.h"
#include "LinkedCameraImplementation.h"
#include "LinkedCameraDebugger.h"
#include <Carna/base/view/SceneProvider.h>
#include <Carna/base/view/Camera.h>
#include <Carna/base/model/Position.h>
#include <Carna/base/Transformation.h>
#include <Carna/base/view/Renderer.h>
#include <Carna/base/Visualization.h>
#include <Carna/base/VisualizationEnvironment.h>

class QGLPixelBuffer;
class QGLContext;

namespace CRA
{



// ----------------------------------------------------------------------------------
// LinkedCamera Adaptive Interface
// ----------------------------------------------------------------------------------

/** \brief  Implementation of \c Carna::Camera that is driven by a \ref Registration and a \ref Localizer.
  *
  * \attention
  * Make sure you are using at least CRA version 1.9 if you are using this class.
  * It did not work properly before this version.
  *
  * \author Leonid Kostrykin
  * \date   23.3.12 - 25.3.13
  */
class LinkedCamera : public Carna::base::view::Camera, public VirtualElement, protected LinkedCameraDebugger
{

public:

    /** \brief Instantiates.
      *
      * Camera calibration will be done using the following files,
      * looked up in the current working directory:
      *
      * - XRayEmpty.trf
      * - XRayEmpty.cof
      * - transformation.ini
      *
      * \throw Carna::AssertionFailure when loading camera calibration files fails.
      */
    LinkedCamera();
    
    /** \brief Instantiates.
      *
      * \throw Carna::AssertionFailure when loading camera calibration files fails.
      */
    LinkedCamera
        ( const std::string& xrayEmptyTrf
        , const std::string& xrayEmptyCof
        , const std::string& transformationIni );

    /** \brief Releases acquired resources.
      */
    virtual ~LinkedCamera();


    virtual void update
        ( const Transformation& bearing
        , const Registration& registration ) override;


    /** \brief Obtains the camera matrix.
      */
    virtual void fetchCameraMatrix( Carna::base::view::Renderer&, Transformation& ) override;

    /** \brief Obtains the projection matrix.
      */
    virtual void fetchProjectionMatrix( Carna::base::view::Renderer&, Transformation& ) override;


    /** \brief Invoked before the render mode routine.
      *
      * Fetches matrices from supplied \ref Registration.
      */
    virtual void openShutter( Carna::base::view::Renderer& ) override;

    /** \brief Invoked after the render mode routine.
      *
      * If \ref setInDebugMode "debug mode is activated", certain additional hints are drawn. 
      */
    virtual void closeShutter( Carna::base::view::Renderer& ) override;


    /** \brief Tells whether the camera does draw extra debugging hints.
      *
      * \since 1.8
      */
    bool isInDebugMode() const;
    
    /** \brief Sets whether the camera does draw extra debugging hints.
      *
      * \since 1.8
      */
    void setInDebugMode( bool );


protected:

    virtual void paintText( const Vector& position, const std::string& text ) override;


private:

    const std::unique_ptr< LinkedCameraImplementation > implementation;

    // ----------------------------------------------------------------------------------

    void compute( Carna::base::view::Renderer& );

    // ----------------------------------------------------------------------------------

    bool inDebugMode;

    Carna::base::view::Renderer* lastUsedRenderer;

}; // LinkedCamera



// ----------------------------------------------------------------------------------
// LinkedCamera Implementation
// ----------------------------------------------------------------------------------

inline
LinkedCamera::LinkedCamera
    ( const std::string& xrayEmptyTrf
    , const std::string& xrayEmptyCof
    , const std::string& transformationIni )

    : Carna::base::view::Camera()
    , implementation( new LinkedCameraImplementation( *this, xrayEmptyTrf, xrayEmptyCof, transformationIni ) )
    , inDebugMode( false )
    , lastUsedRenderer( nullptr )
{
}


inline
LinkedCamera::LinkedCamera()
    : implementation( new LinkedCameraImplementation( *this ) )
    , inDebugMode( false )
    , lastUsedRenderer( nullptr )
{
}


inline
LinkedCamera::~LinkedCamera()
{
}


inline
void LinkedCamera::update( const Transformation& physical_bearing, const Registration& registration )
{
    implementation->update( physical_bearing, registration );

    emit viewChanged();
}


inline
void LinkedCamera::compute( Carna::base::view::Renderer& renderer )
{
    implementation->compute( renderer.shortestTargetSide() );

    // ----------------------------------------------------------------------------------

    const Transformation reverse_trafo = implementation->registration().getTransformation().inverse();

    const Vector model_center_offset = Carna::base::model::Position::fromVolumeUnits
        ( renderer.provider.scene, 0.5, 0.5, 0.5 ).toMillimeters();

    fromReferenceBase = implementation->cameraTransformation();
    fromLocalToReferenceBase = implementation->physicalBearing();
    fromSceneSpaceToReferenceBase = reverse_trafo
        * Transformation().translate( model_center_offset.x()
        , model_center_offset.y()
        , model_center_offset.z() );

    implementation->setCameraTransformation
        ( implementation->cameraTransformation()
        * fromSceneSpaceToReferenceBase );
}


inline
void LinkedCamera::fetchCameraMatrix( Carna::base::view::Renderer& renderer, Transformation& out )
{
    out = implementation->cameraTransformation();
}


inline
void LinkedCamera::fetchProjectionMatrix( Carna::base::view::Renderer& renderer, Transformation& out )
{
    out = implementation->projectionTransformation();
}


inline
void LinkedCamera::openShutter( Carna::base::view::Renderer& renderer )
{
    if( implementation->hasRegistration() )
    {
        this->compute( renderer );
    }
}


inline
void LinkedCamera::closeShutter( Carna::base::view::Renderer& renderer )
{
    if( isInDebugMode() )
    {
        renderer.setSquareViewport();

        this->lastUsedRenderer = &renderer;
        this->paintDebugInfo( *implementation );
    }
}


inline
void LinkedCamera::paintText( const Vector& position, const std::string& text )
{
    lastUsedRenderer->module().environment().paintText( position, text );
}


inline
bool LinkedCamera::isInDebugMode() const
{
    return inDebugMode;
}


inline
void LinkedCamera::setInDebugMode( bool inDebugMode )
{
    if( this->inDebugMode != inDebugMode )
    {
        this->inDebugMode = inDebugMode;
        emit viewChanged();
    }
}



}  // namespace CRA

#endif // LINKEDCAMERA_H_2521354512
