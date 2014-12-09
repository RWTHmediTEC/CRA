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

#include "LazyLocalizer.h"

namespace CRA
{



// ----------------------------------------------------------------------------------
// LazyLocalizer
// ----------------------------------------------------------------------------------

const unsigned int LazyLocalizer::defaultLazynessThreshold = 100;


LazyLocalizer::LazyLocalizer( Localizer& service )
    : service( service )
    , lazynessThreshold( defaultLazynessThreshold )
{
}


bool LazyLocalizer::fetch( const std::string& port, Transformation& transformation )
{
    StringToTime::iterator it = cacheCurrentness.find( port );

    if( it == cacheCurrentness.end() )
    {
        cacheCurrentness[ port ] = QTime::currentTime();

        const bool visible = service.fetch( port, transformation );

        orientationCache[ port ] = transformation;

        visibilityCache[ port ] = visible;

        return visible;
    }
    else
    {
        if( it->second.elapsed() > signed( getLazynessThreshold() ) )
        {
            it->second = QTime::currentTime();

            const bool visible = service.fetch( port, transformation );

            orientationCache[ port ] = transformation;

            visibilityCache[ port ] = visible;

            return visible;
        }
        else
        {
            transformation = orientationCache[ port ];

            return visibilityCache[ port ];
        }
    }
}



}  // namespace CRA
