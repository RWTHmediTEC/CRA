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

#ifndef LINKEDOBJECT_H_2521354512
#define LINKEDOBJECT_H_2521354512

#include "VirtualElement.h"
#include "Registration.h"
#include <Carna/base/model/Position.h>
#include <Carna/base/model/Object3D.h>

namespace CRA
{



// ----------------------------------------------------------------------------------
// LinkedObject Adaptive Interface
// ----------------------------------------------------------------------------------

/** \brief  Adapter which maps the VirtualElement interface to this of \c Object3D.
  *
  * \image  html api01.png
  *
  * \author Leonid Kostrykin
  * \date   23.3.12 - 26.9.12
  */
class LinkedObject : public VirtualElement
{

public:

    /** \brief  Instantiates.
      */
    LinkedObject( Carna::base::model::Object3D& );


    virtual void update( const Transformation& orientation
                       , const Registration& registration ) override;


    /** \brief  References the controlled 3D object.
      */
    Carna::base::model::Object3D& object;

}; // LinkedObject



// ----------------------------------------------------------------------------------
// LinkedObject Implementation
// ----------------------------------------------------------------------------------

inline
LinkedObject::LinkedObject( Carna::base::model::Object3D& object )
    : object( object )
{
}


inline
void LinkedObject::update( const Transformation& bearing, const Registration& registration )
{
    const Transformation orientation = registration.getTransformation() * bearing;

    Carna::base::model::Position position = Carna::base::model::Position::fromMillimeters( object.model
        , orientation.a14()
        , orientation.a24()
        , orientation.a34() );

    Transformation rotation = orientation;
    rotation.a14() = rotation.a24() = rotation.a34() = 0;

    object.setPosition( position );
    object.setRotation( rotation );
}



}  // namespace CRA

#endif // LINKEDOBJECT_H_2521354512
