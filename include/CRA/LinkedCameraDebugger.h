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

#ifndef LINKEDCAMERADEBUGGER_H_2521354512
#define LINKEDCAMERADEBUGGER_H_2521354512

#include "cra_global.h"
#include "Transformation.h"

namespace CRA
{

class LinkedCameraImplementation;



// ----------------------------------------------------------------------------------
// LinkedCameraDebugger
// ----------------------------------------------------------------------------------

/** \brief  Provides interface for \ref LinkedCamera debugging.
  *
  * \author Leonid Kostrykin
  * \date   18.4.13
  */
class CRA_EXPORT LinkedCameraDebugger
{

public:

    /** \brief Instantiates.
      */
    LinkedCameraDebugger();

    virtual ~LinkedCameraDebugger();


    /** \brief  Paints \ref LinkedCamera debugging hints.
      */
    void paintDebugInfo( const LinkedCameraImplementation& implementation );


    /** \brief Holds the inverse of transformation into coordinate system of reference base.
      */
    Transformation fromReferenceBase;
    
    /** \brief Holds the transformation from C-arm to the reference base coordinate system.
      */
    Transformation fromLocalToReferenceBase;
    
    /** \brief Holds the scene space bearing relatively to the reference base coordinate system.
      */
    Transformation fromSceneSpaceToReferenceBase;

    
protected:

    /** \brief  Paints text at the given location.
      */
    virtual void paintText( const Vector& position, const std::string& text ) = 0;

}; // LinkedCameraDebugger



}  // namespace CRA

#endif // LINKEDCAMERADEBUGGER_H_2521354512
