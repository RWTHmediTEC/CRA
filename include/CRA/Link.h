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

#ifndef LINK_H_2521354512
#define LINK_H_2521354512

#include "cra_global.h"

namespace CRA
{

class Tool;
class VirtualElement;



// ----------------------------------------------------------------------------------
// Link
// ----------------------------------------------------------------------------------

/** \brief	Tuple of a one Tool and VirtualElement instances.
  *
  * When \c %Link instances are provided to some Registration, the linked virtual
  * scene element gets moved when their physical representations' position changes.
  *
  * A \c %Link instance represents scene elements with a physical representation and a
  * virtual representation.
  *
  * \author Leonid Kostrykin
  * \date   23.3.12 - 28.3.12
  */
class CRA_EXPORT Link
{

public:

    /** \brief	Instantiates.
      */
    Link( Tool& tool, VirtualElement& virtualElement )
        : tool( tool )
        , virtualElement( virtualElement )
    {
    }


    /** \brief	References the associated physical representation.
      */
    Tool& tool;

    /** \brief	References the associated virtual representation.
      */
    VirtualElement& virtualElement;

}; // Link



/** \brief	Defines relation for Link instances using the address of their tools.
  *
  * \relates Link
  */
inline bool operator<( const Link& l, const Link& r )
{
    return &( l.tool ) < &( r.tool );
}



}  // namespace CRA

#endif // LINK_H_2521354512
