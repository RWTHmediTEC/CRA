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

#include "LinkedObject.h"
#include "Registration.h"
#include <Carna/Object3D.h>

namespace CRA
{



// ----------------------------------------------------------------------------------
// LinkedObject
// ----------------------------------------------------------------------------------

LinkedObject::LinkedObject( Carna::Object3D& object )
    : object( object )
{
}


void LinkedObject::update( const Carna::Tools::Transformation& bearing, const Registration& registration )
{
    const Carna::Tools::Transformation orientation = registration.getTransformation() * bearing;

    Carna::Position position = Carna::Position::fromMillimeters( object.model
                                                               , orientation.a14()
                                                               , orientation.a24()
                                                               , orientation.a34() );

    Carna::Tools::Transformation rotation = orientation;
    rotation.a14() = rotation.a24() = rotation.a34() = 0;

    object.setPosition( position );
    object.setRotation( rotation );
}



}  // namespace CRA
