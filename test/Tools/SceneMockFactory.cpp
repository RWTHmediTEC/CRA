#include "SceneMockFactory.h"
#include <Carna/base/model/Scene.h>
#include <Carna/base/model/UInt16Volume.h>
#include <Carna/base/Composition.h>



// ----------------------------------------------------------------------------------
// SceneMockFactory :: Dimensions
// ----------------------------------------------------------------------------------

SceneMockFactory::Dimensions::Dimensions( double width, double height, double depth )
    : width( width )
    , height( height )
    , depth( depth )
{
}


SceneMockFactory::Dimensions SceneMockFactory::Dimensions::fromCentimeters( double width, double height, double depth )
{
    return Dimensions( width * 10, height * 10, depth * 10 );
}



// ----------------------------------------------------------------------------------
// SceneMockFactory
// ----------------------------------------------------------------------------------

SceneMockFactory::SceneMockFactory( const Dimensions& dimensions, double voxelsPerMillimeter )
    : volumeSize( [&]()->Carna::base::Vector3ui
            {
                Carna::base::Vector3ui size;

                size.x = static_cast< unsigned int >( dimensions.width  * voxelsPerMillimeter + 0.5 );
                size.y = static_cast< unsigned int >( dimensions.height * voxelsPerMillimeter + 0.5 );
                size.z = static_cast< unsigned int >( dimensions.depth  * voxelsPerMillimeter + 0.5 );

                return size;
            }
        () )
    , spacingX( 1 / voxelsPerMillimeter )
    , spacingY( 1 / voxelsPerMillimeter )
    , spacingZ( 1 / voxelsPerMillimeter )
{
}


SceneMockFactory::SceneMockFactory( const Carna::base::Vector3ui& volumeSize, const double spacingX, const double spacingY, const double spacingZ )
    : volumeSize( volumeSize )
    , spacingX( spacingX )
    , spacingY( spacingY )
    , spacingZ( spacingZ )
{
}


Carna::base::model::Scene* SceneMockFactory::createSceneMock() const
{
    Carna::base::model::Volume* const volume = new Carna::base::model::UInt16Volume( volumeSize );

    Carna::base::model::Scene* const model = new Carna::base::model::Scene
        ( new Carna::base::Composition< Carna::base::model::Volume >( volume )
        , spacingX
        , spacingY
        , spacingZ );

    return model;
}
