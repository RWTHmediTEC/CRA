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

#include "LocalizerMock.h"



// ----------------------------------------------------------------------------------
// LocalizerMock
// ----------------------------------------------------------------------------------

bool LocalizerMock::fetch( const std::string& port, CRA::Transformation& out )
{
    return true;
}
