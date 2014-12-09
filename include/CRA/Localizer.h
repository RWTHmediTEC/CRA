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

#ifndef LOCALIZER_H_2521354512
#define LOCALIZER_H_2521354512

#include "Transformation.h"

namespace CRA
{



// ----------------------------------------------------------------------------------
// Localizer
// ----------------------------------------------------------------------------------

/** \brief	Defines interface for querying the bearing of tools,
  *         addressing them by ports.
  *
  * \author Leonid Kostrykin
  * \date   23.3.12 - 28.3.12
  */
class Localizer
{

public:

    /** \brief	Does nothing.
      */
    virtual ~Localizer()
    {
    }


    /** \brief	Queries the bearing of the tool specified by some port.
      */
    virtual bool fetch( const std::string& port, Transformation& out ) = 0;

}; // Localizer



}  // namespace CRA

#endif // LOCALIZER_H_2521354512
