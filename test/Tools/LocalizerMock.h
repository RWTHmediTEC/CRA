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

#pragma once

#include <CRA/Localizer.h>



// ----------------------------------------------------------------------------------
// LocalizerMock
// ----------------------------------------------------------------------------------

class LocalizerMock : public CRA::Localizer
{

public:

    virtual bool fetch( const std::string& port, CRA::Transformation& out ) override;

}; // LocalizerMock
