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

#include "glew.h"
#include "LinkedCameraDebugger.h"
#include "LinkedCameraImplementation.h"
#include "Registration.h"

namespace CRA
{



// ----------------------------------------------------------------------------------
// glMultMatrix
// ----------------------------------------------------------------------------------

static void glMultMatrix( const Transformation& m )
{
    float a[ 16 ];
    for( int i = 0; i < 16; ++i )
    {
        a[ i ] = m.getTransformationMatrix()( i % 4, i / 4 );
    }
    glMultMatrixf( a );
}



// ----------------------------------------------------------------------------------
// glLoadMatrix
// ----------------------------------------------------------------------------------

static void glLoadMatrix( const Transformation& m )
{
    glLoadIdentity();
    glMultMatrix( m );
}



// ----------------------------------------------------------------------------------
// LinkedCameraDebugger
// ----------------------------------------------------------------------------------

LinkedCameraDebugger::LinkedCameraDebugger()
{
}


LinkedCameraDebugger::~LinkedCameraDebugger()
{
}


void LinkedCameraDebugger::paintDebugInfo( const LinkedCameraImplementation& implementation )
{
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadMatrix( implementation.cameraTransformation() );
    glTranslatef( -0.5f, -0.5f, -0.5f );

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadMatrix( implementation.projectionTransformation() );

    glMatrixMode( GL_MODELVIEW );
    glColor4f( 0.5f, 0.f, 0.f, 1.f );
    glLineWidth( 1.f );

    glBegin( GL_LINE_LOOP );

    glVertex3f( 0, 0, 0 );
    glVertex3f( 1, 0, 0 );
    glVertex3f( 1, 1, 0 );
    glVertex3f( 0, 1, 0 );

    glEnd();
    glBegin( GL_LINE_LOOP );

    glVertex3f( 0, 0, 1 );
    glVertex3f( 1, 0, 1 );
    glVertex3f( 1, 1, 1 );
    glVertex3f( 0, 1, 1 );

    glEnd();
    glBegin( GL_LINES );

    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, 0, 1 );

    glVertex3f( 1, 0, 0 );
    glVertex3f( 1, 0, 1 );

    glVertex3f( 1, 1, 0 );
    glVertex3f( 1, 1, 1 );

    glVertex3f( 0, 1, 0 );
    glVertex3f( 0, 1, 1 );

    glEnd();

    // ----------------------------------------------------------------------------------

    glLoadMatrix( fromReferenceBase );
    glPushMatrix();
    float l;

    // draw reference base

    l = 100.f;
    glLineWidth( 3.f );

    glColor3f( 1, 0, 0 );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( l, 0, 0 );
    glEnd();

    glColor3f( 0, 1, 0 );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, l, 0 );
    glEnd();

    glColor3f( 0, 0, 1 );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, 0, l );
    glEnd();

    glColor3f( 1, 1, 1 );
    this->paintText( Vector( 0, 0, 0 ), "Reference" );

    // draw reference base to local

    const Vector local_origin
        ( fromLocalToReferenceBase.a14()
        , fromLocalToReferenceBase.a24()
        , fromLocalToReferenceBase.a34() );

    glLineWidth( 1.f );
    glColor3f( 1, 1, 1 );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( local_origin.x(), local_origin.y(), local_origin.z() );
    glEnd();

    this->paintText
        ( Vector
            ( local_origin.x() / 2
            , local_origin.y() / 2
            , local_origin.z() / 2 )
        , ( QString::number( local_origin.norm() ) + " mm" ).toStdString() );

    // draw reference base to scene space

    const Vector scene_origin
        ( fromSceneSpaceToReferenceBase.a14()
        , fromSceneSpaceToReferenceBase.a24()
        , fromSceneSpaceToReferenceBase.a34() );

    glLineWidth( 1.f );
    glColor3f( 1, 1, 1 );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( scene_origin.x(), scene_origin.y(), scene_origin.z() );
    glEnd();

    this->paintText
        ( Vector
            ( scene_origin.x() / 2
            , scene_origin.y() / 2
            , scene_origin.z() / 2 )
        , ( QString::number( scene_origin.norm() ) + " mm" ).toStdString() );

    // draw local to scene space distance

    glLineWidth( 1.f );
    glColor3f( 0.5f, 0.5f, 0.5f );
    glBegin( GL_LINES );
    glVertex3f( local_origin.x(), local_origin.y(), local_origin.z() );
    glVertex3f( scene_origin.x(), scene_origin.y(), scene_origin.z() );
    glEnd();

    const Vector scene_origin_to_scene_space_mid = local_origin + ( scene_origin - local_origin ) / 2;

    this->paintText
        ( Vector
            ( scene_origin_to_scene_space_mid.x()
            , scene_origin_to_scene_space_mid.y()
            , scene_origin_to_scene_space_mid.z() )
        , ( QString::number( ( scene_origin - local_origin ).norm() ) + " mm" ).toStdString() );

    // draw local (C-Arm)

    glMultMatrix( fromLocalToReferenceBase );

    l = 50.f;
    glLineWidth( 1.f );

    glColor3f( 1, 0, 0 );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( l, 0, 0 );
    glEnd();

    glColor3f( 0, 1, 0 );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, l, 0 );
    glEnd();

    glColor3f( 0, 0, 1 );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, 0, l );
    glEnd();

    glColor3f( 1, 1, 1 );
    this->paintText( Vector( 0, 0, 0 ), "Local" );

    // draw scene space

    glPopMatrix();
    glMultMatrix( fromSceneSpaceToReferenceBase );

    l = 0.5f;
    glLineWidth( 2.f );

    glColor3f( 1, 0, 0 );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( l, 0, 0 );
    glEnd();

    glColor3f( 0, 1, 0 );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, l, 0 );
    glEnd();

    glColor3f( 0, 0, 1 );
    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, 0, l );
    glEnd();

    glColor3f( 1, 1, 1 );
    this->paintText( Vector( 0, 0, 0 ), "Scene" );

    // ----------------------------------------------------------------------------------

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();

    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
}



}  // namespace CRA
