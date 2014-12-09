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

#include "ToolByPort.h"
#include "Localizer.h"

namespace CRA
{



// ----------------------------------------------------------------------------------
// ToolByPort
// ----------------------------------------------------------------------------------

ToolByPort::ToolByPort( Localizer& localizer, const std::string& port, const std::string& name )
    : Tool( name )
    , localizer( localizer )
    , port( port )
{
}


ToolByPort::ToolByPort( Localizer& localizer, const std::string& port )
    : Tool( port )
    , localizer( localizer )
    , port( port )
{
}


const Transformation& ToolByPort::getOrientation() const
{
    updateFromLocalizer();

    return orientation;
}


bool ToolByPort::isVisible() const
{
    updateFromLocalizer();

    return visible;
}


void ToolByPort::updateFromLocalizer() const
{
    visible = localizer.fetch( port, orientation );

    if( visible )
    {
        const auto rotation = orientation.getTransformationMatrix().topLeftCorner( 3, 3 );
        const auto offset = Vector::Vector3T( getOffset().x(), getOffset().y(), getOffset().z() );
        Vector dt = Vector( rotation * offset );

        orientation.a14() += dt.x();
        orientation.a24() += dt.y();
        orientation.a34() += dt.z();
    }
}



}  // namespace CRA
