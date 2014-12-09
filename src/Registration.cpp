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

#include "Registration.h"
#include "Link.h"
#include "VirtualElement.h"
#include "Tool.h"

namespace CRA
{



// ----------------------------------------------------------------------------------
// Registration
// ----------------------------------------------------------------------------------

Registration::Registration( Tool& referenceBase )
    : referenceBase( &referenceBase )
    , customTranslation( nullptr )
{
}


Registration::~Registration()
{
}


void Registration::setReferenceBase( Tool& referenceBase )
{
    this->referenceBase = &referenceBase;
}


Tool& Registration::getReferenceBase() const
{
    return *referenceBase;
}


void Registration::setTransformation( const Transformation& transformation )
{
    this->transformation = transformation;
    this->originalTranslation = Vector( transformation.a14()
                                                    , transformation.a24()
                                                    , transformation.a34() );

    applyCustomTranslation();
}


const Transformation& Registration::getTransformation() const
{
    return transformation;
}


void Registration::setCustomTranslation( const Vector& customTranslation )
{
    this->customTranslation.reset( new Vector( customTranslation ) );

    applyCustomTranslation();
}


void Registration::removeCustomTranslation()
{
    customTranslation.reset();

    transformation.a14() = originalTranslation.x();
    transformation.a24() = originalTranslation.y();
    transformation.a34() = originalTranslation.z();

    emit transformationChanged( this->transformation );
    emit transformationChanged();
}


const Vector& Registration::getCustomTranslation() const
{
    assert( customTranslation.get() != 0 );

    return *customTranslation;
}


void Registration::applyCustomTranslation()
{
    if( customTranslation )
    {
        const Vector& position = *customTranslation;

        transformation.a14() = position.x();
        transformation.a24() = position.y();
        transformation.a34() = position.z();
    }

    emit transformationChanged( this->transformation );
    emit transformationChanged();
}


bool Registration::hasCustomTranslation() const
{
    return customTranslation.get() != nullptr;
}


void Registration::add( const Link& link )
{
    links.insert( link );
}


void Registration::remove( const Link& link )
{
    links.erase( link );
}


void Registration::updateVirtualElements()
{
    Transformation relativeOrientation;

    for( std::set< Link >::iterator it = links.begin(); it != links.end(); ++it )
    {
        it->tool.computeRelativeOrientation( getReferenceBase(), relativeOrientation );

        it->virtualElement.update( relativeOrientation, *this );
    }
}



}  // namespace CRA
