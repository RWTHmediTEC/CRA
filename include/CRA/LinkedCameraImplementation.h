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

#ifndef LINKEDCAMERAIMPLEMENTATION_H_2521354512
#define LINKEDCAMERAIMPLEMENTATION_H_2521354512

#include "cra_global.h"
#include "Transformation.h"
#include <memory>
#include <string>

namespace CRA
{

class LinkedCamera;
class Registration;



// ----------------------------------------------------------------------------------
// LinkedCameraImplementation
// ----------------------------------------------------------------------------------

class CRA_EXPORT LinkedCameraImplementation
{

public:

    LinkedCameraImplementation( LinkedCamera& );

    LinkedCameraImplementation
        ( LinkedCamera& self
        , const std::string& xrayEmptyTrf
        , const std::string& xrayEmptyCof
        , const std::string& transformationIni );

    ~LinkedCameraImplementation();


    void compute( unsigned int shortestTargetSide );

    void update( const Transformation& physical_bearing, const Registration& registration );

    bool hasRegistration() const;

    const Registration& registration() const;

    void setCameraTransformation( const Transformation& );

    const Transformation& cameraTransformation() const;

    const Transformation& projectionTransformation() const;

    const Transformation& physicalBearing() const;


private:

    class Details;

    const std::unique_ptr< Details > pimpl;

}; // LinkedCameraImplementation



}  // namespace CRA

#endif // LINKEDCAMERAIMPLEMENTATION_H_2521354512
