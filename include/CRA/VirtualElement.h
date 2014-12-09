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

#ifndef VIRTUALELEMENT_H_2521354512
#define VIRTUALELEMENT_H_2521354512

#include "cra_global.h"
#include "Transformation.h"

namespace CRA
{

class Tool;
class Registration;



// ----------------------------------------------------------------------------------
// VirtualElement
// ----------------------------------------------------------------------------------

/** \brief  Represents a virtual scene element, maybe an object or the camera.
  *
  * \image  html api01.png
  *
  * \author Leonid Kostrykin
  * \date   23.3.12 - 26.9.12
  */
class CRA_EXPORT VirtualElement
{

public:

    /** \brief  Does nothing.
      */
    virtual ~VirtualElement()
    {
    }


    /** \brief  Updates the represented scene element's bearing.
      *
      * \param  bearing         Is the orientation of the associated tool to the reference base.
      * \param  registration    References the current registration.
      */
    virtual void update( const Transformation& bearing
                       , const Registration& registration ) = 0;

}; // VirtualElement



}  // namespace CRA

#endif // VIRTUALELEMENT_H_2521354512
