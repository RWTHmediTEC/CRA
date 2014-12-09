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

#include "BuildTest.h"
#include "LocalizerMock.h"
#include "SceneMockFactory.h"
#include <Carna/base/view/Point3D.h>
#include <Carna/base/model/Scene.h>
#include <CRA/Localizer.h>
#include <CRA/ToolByPort.h>
#include <CRA/Link.h>
#include <CRA/LinkedObject.h>
#include <CRA/LinkedCamera.h>
#include <CRA/Registration.h>



// ----------------------------------------------------------------------------------
// BuildTest
// ----------------------------------------------------------------------------------

BuildTest::~BuildTest()
{
}


void BuildTest::initTestCase()
{
    disableQDebug();

    const SceneMockFactory sceneFactory( Carna::base::Vector3ui( 50, 50, 50 ), 0.2f, 0.2f, 0.2f );
    scene.reset( sceneFactory.createSceneMock() );
}


void BuildTest::cleanupTestCase()
{
    scene.reset();
}


void BuildTest::init()
{
}


void BuildTest::cleanup()
{
}


void BuildTest::testMinimumScenario()
{
    LocalizerMock tracking_service;

 // define trackable tools

    CRA::ToolByPort reference_base( tracking_service, "port0" );
    CRA::ToolByPort tool1( tracking_service, "port1" );
    CRA::ToolByPort tool2( tracking_service, "port2" );

 // define scene elements

    Carna::base::view::Point3D point( *scene );
    CRA::LinkedCamera linked_camera
        ( SOURCE_PATH + "/res/XRayEmpty.trf"
        , SOURCE_PATH + "/res/XRayEmpty.cof"
        , SOURCE_PATH + "/res/Transformation.ini" );

 // define CRA adapters

    CRA::LinkedObject linked_point( point );

 // define registration

    CRA::Registration registration( reference_base );
    registration.add( CRA::Link( tool1, linked_point ) );
    registration.add( CRA::Link( tool2, linked_camera ) );

 // trigger registration once

    registration.updateVirtualElements();
}
