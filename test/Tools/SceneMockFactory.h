/*
 *  Copyright (C) 2010 - 2014 Leonid Kostrykin
 *
 *  Chair of Medical Engineering (mediTEC)
 *  RWTH Aachen University
 *  Pauwelsstr. 20
 *  52074 Aachen
 *  Germany
 *
 */

#pragma once

#include <Carna/Carna.h>
#include <Carna/base/Vector3.h>



// ----------------------------------------------------------------------------------
// SceneMockFactory
// ----------------------------------------------------------------------------------

class SceneMockFactory 
{

public:

    struct Dimensions
    {
        double width;
        double height;
        double depth;

        Dimensions( double width, double height, double depth );

        static Dimensions fromCentimeters( double width, double height, double depth );
    };


    SceneMockFactory( const Dimensions& size, double voxelsPerMillimeter );

    SceneMockFactory( const Carna::base::Vector3ui& volumeSize, const double spacingX, const double spacingY, const double spacingZ );


    Carna::base::model::Scene* createSceneMock() const;

    const Carna::base::Vector3ui volumeSize;

    const double spacingX;
    const double spacingY;
    const double spacingZ;

}; // SceneMockFactory
