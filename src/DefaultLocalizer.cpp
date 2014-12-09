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

#include "DefaultLocalizer.h"
#include "DefaultLocalizerDetails.h"
#include <QFileInfo>
#include <QApplication>

namespace CRA
{



// ----------------------------------------------------------------------------------
// DefaultLocalizer :: Details
// ----------------------------------------------------------------------------------

DefaultLocalizer::Details::Details()
{
}



// ----------------------------------------------------------------------------------
// DefaultLocalizer
// ----------------------------------------------------------------------------------

DefaultLocalizer::DefaultLocalizer( const std::string& iniFile )
    : pimpl( new Details() )
{
    loadFromIni( iniFile );
}


DefaultLocalizer::~DefaultLocalizer()
{
    requestState( asleep );
}


void DefaultLocalizer::requestState( State state )
{
    switch( state )
    {

    case ready:
        {
            if( !pimpl->localizer.isTracking() )
            {
                pimpl->localizer.startTracking();

                assert( pimpl->localizer.isTracking() );
            }
            break;
        }

    case asleep:
        {
            if( pimpl->localizer.isTracking() )
            {
                pimpl->localizer.stopTracking();

                assert( !pimpl->localizer.isTracking() );
            }
            break;
        }

    default:
        {
            throw std::logic_error( "unknown state request" );
        }

    }
}


bool DefaultLocalizer::fetch( const std::string& port, Transformation& out )
{
    requestState( ready );

    std::vector< CToolData* > tdv;

    CToolData td;
    td.bVisible = false;

    td.setSzPort( port );

    tdv.push_back( &td );

    pimpl->localizer.getToolData( tdv );

    if( td.isVisible() )
    {
        for( int i = 0; i < 3; ++i )
        for( int j = 0; j < 3; ++j )
        {
            out.getTransformationMatrix()( i, j ) = td.mR( i, j );
        }

        for( int i = 0; i < 3; ++i )
        {
            out.getTransformationMatrix()( i, 3 ) = td.vT( i );
        }

        out.a44() = 1;

        return true;
    }
    else
    {
        return false;
    }
}


void DefaultLocalizer::loadFromIni( const std::string& iniFile )
{
    requestState( asleep );

    QFileInfo iniFileInfo( QString::fromStdString( iniFile ) );
    if( iniFileInfo.exists() )
    {
        QString iniFileName( iniFileInfo.fileName() );
        QString iniFilePath( iniFileInfo.absolutePath() );

        QApplication::setOverrideCursor( Qt::WaitCursor );
        bool success = !pimpl->localizer.open( iniFilePath.toStdString(), iniFileName.toStdString() );
        QApplication::restoreOverrideCursor();

        if( !success )
        {
            throw illegalIniFile();
        }
    }
    else
    {
        throw missingIniFile();
    }
}



}  // namespace CRA
