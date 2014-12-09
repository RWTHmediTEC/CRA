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

#ifndef DEFAULTLOCALIZER_DETAILS_H_2521354512
#define DEFAULTLOCALIZER_DETAILS_H_2521354512

#include "DefaultLocalizer.h"
#include <localizerDLL/Localizer.h>

namespace CRA
{



// ----------------------------------------------------------------------------------
// DefaultLocalizer
// ----------------------------------------------------------------------------------

class DefaultLocalizer :: Details
{

public:

    Details();


    CLocalizer localizer;

}; // DefaultLocalizer :: Details



}  // namespace CRA

#endif // DEFAULTLOCALIZER_DETAILS_H_2521354512
