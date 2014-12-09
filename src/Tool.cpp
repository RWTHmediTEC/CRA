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

#include "Tool.h"

namespace CRA
{



// ----------------------------------------------------------------------------------
// get3x3
// ----------------------------------------------------------------------------------

static inline Transformation get3x3( const Transformation& m )
{
    Transformation result = m;
    result.a14() = result.a24() = result.a34() = 0;
    return result;
}



// ----------------------------------------------------------------------------------
// computeRelativeOrientation
// ----------------------------------------------------------------------------------

static void computeRelativeOrientation( const Transformation& subject
                                      , const Transformation& reference
                                      , Transformation& out )
{
    const Transformation transposedReference3x3 = Transformation( get3x3( reference ).getTransformationMatrix().transpose() );

    out = transposedReference3x3 * get3x3( subject );

    const Vector subjectPosition( subject.a14(), subject.a24(), subject.a34(), 1 );
    const Vector referenceBasePosition( reference.a14(), reference.a24(), reference.a34(), 0 );
    const Vector relativePosition = transposedReference3x3 * ( subjectPosition - referenceBasePosition );

    out.a14() = relativePosition.x();
    out.a24() = relativePosition.y();
    out.a34() = relativePosition.z();
}



// ----------------------------------------------------------------------------------
// Tool
// ----------------------------------------------------------------------------------

Tool::Tool( const std::string& name )
    : name( name )
    , offset( 0., 0., 0. )
{
}


void Tool::setName( const std::string& name )
{
    this->name = name;

    emit renamed();
    emit renamed( name );
    emit renamed( QString::fromStdString( name ) );
}


void Tool::setName( const QString& name )
{
    this->setName( name.toStdString() );
}


const std::string& Tool::getName() const
{
    return name;
}


void Tool::computeRelativeOrientation
    ( const Tool& reference
    , Transformation& out ) const
{
    ::CRA::computeRelativeOrientation( this->getOrientation(), reference.getOrientation(), out );
}


void Tool::setOffset( const Vector& offset )
{
    if( ( this->offset - offset ).norm() > 1e-6 )
    {
        this->offset = offset;

        emit offsetChanged();
        emit offsetChanged( this->offset );
    }
}


const Vector& Tool::getOffset() const
{
    return offset;
}



}  // namespace CRA
