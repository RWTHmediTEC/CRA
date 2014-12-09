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

#ifndef LINKEDCAMERAIMPLEMENTATION_DETAILS_H_2521354512
#define LINKEDCAMERAIMPLEMENTATION_DETAILS_H_2521354512

#include "LinkedCameraImplementation.h"
#include "Transformation.h"

#pragma warning( push )
#pragma warning( disable:4251 )

#include <CameraCalibration/Trafo.h>

#pragma warning( pop )

class QGLPixelBuffer;
class QGLContext;

namespace CRA
{



// ----------------------------------------------------------------------------------
// LinkedCameraImplementation :: Details
// ----------------------------------------------------------------------------------

class LinkedCameraImplementation :: Details
{

public:

    LinkedCamera& self;

    Details( LinkedCamera& );

    Details
        ( LinkedCamera& self
        , const std::string& xrayEmptyTrf
        , const std::string& xrayEmptyCof
        , const std::string& transformationIni );

    ~Details();

    // ----------------------------------------------------------------------------------

    CTrafo trafo;

    Transformation camera, projection;

 // ----------------------------------------------------------------------------------

    const std::auto_ptr< QGLPixelBuffer > pbuffer;

    QGLContext* const calibrationContext;
    
 // ----------------------------------------------------------------------------------

    void init
        ( const std::string& xrayEmptyTrf
        , const std::string& xrayEmptyCof
        , const std::string& transformationIni );

    void update( unsigned int shortestTargetSide );
    
 // ----------------------------------------------------------------------------------

    Transformation physicalBearing;

    const Registration* registration;

}; // LinkedCameraImplementation :: Details



}  // namespace CRA

#endif // LINKEDCAMERAIMPLEMENTATION_DETAILS_H_2521354512
