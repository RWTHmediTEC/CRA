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

#ifndef TRANSFORMATION_H_2521354512
#define TRANSFORMATION_H_2521354512

#include <TRTK/Transform3D.hpp>
#include <TRTK/Coordinate.hpp>

namespace CRA
{



// ----------------------------------------------------------------------------------
// Transformation
// ----------------------------------------------------------------------------------

/** \brief	Defines matrix and vector transformations through TRTK classes.
  */
typedef TRTK::Transform3D< double > Transformation;



// ----------------------------------------------------------------------------------
// Vector
// ----------------------------------------------------------------------------------

/** \brief	Defines vectors through TRTK classes.
  */
typedef TRTK::Coordinate< double > Vector;



}  // namespace CRA

#endif // TRANSFORMATION_H_2521354512
