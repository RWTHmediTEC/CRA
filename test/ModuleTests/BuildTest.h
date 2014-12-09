/*
 *  Copyright (C) 2010 - 2014 Leonid Kostrykin
 *
 *  Chair of Medical Engineering (mediTEC)
 *  RWTH Aachen University
 *  Pauwelsstr. 20
 *  52074 Aachen
 *  Germany
 *
 */

#pragma once

#include <memory>



// ----------------------------------------------------------------------------------
// BuildTest
// ----------------------------------------------------------------------------------

class BuildTest : public QObject
{

    Q_OBJECT

public:

    ~BuildTest();

private slots:

    /** \brief  Called before the first test function is executed.
      */
    void initTestCase();

    /** \brief  Called after the last test function is executed.
      */
    void cleanupTestCase();

    /** \brief  Called before each test function is executed
      */
    void init();

    /** \brief  Called after each test function is executed
      */
    void cleanup();

 // ----------------------------------------------------------------------------------

    /** \brief  Tests minimum code utilization.
      */
    void testMinimumScenario();

 // ----------------------------------------------------------------------------------

private:

    std::unique_ptr< Carna::base::model::Scene > scene;
    
}; // BuildTest
