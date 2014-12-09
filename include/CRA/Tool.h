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

#ifndef TOOL_H_2521354512
#define TOOL_H_2521354512

#include "cra_global.h"
#include "Transformation.h"
#include <string>
#include <QObject>

namespace CRA
{



// ----------------------------------------------------------------------------------
// Tool
// ----------------------------------------------------------------------------------

/** \brief	Represents a trackable tool.
  *
  * Every tool has a name. The choice of a certain name has no further impact.
  *
  * \author Leonid Kostrykin
  * \date   23.3.12 - 22.2.13
  */
class CRA_EXPORT Tool : public QObject
{

    Q_OBJECT

public:

    /** \brief	Creates a new tool.
      */
    Tool( const std::string& name );


    /** \brief	Tells this tool's name.
      */
    const std::string& getName() const;

    /** \brief  Tells the offset of this tool's origin in it's local
      *         coordinate system.
      *
      * \since  1.5
      *
      * \see    \ref setOffset, \ref getOrientation
      */
    const Vector& getOffset() const;


    /** \brief	Tells the current bearing of this tool.
      *
      * The result reflects \ref setOffset "the currently set offset".
      */
    virtual const Transformation& getOrientation() const = 0;

    /** \brief	Computes the relative bearing of this tool to another.
      */
    virtual void computeRelativeOrientation( const Tool& reference
                                           , Transformation& out ) const;


    /** \brief	Tells whether this tool is currently visible.
      */
    virtual bool isVisible() const = 0;


public slots:

    /** \brief	Renames this tool.
      */
    void setName( const std::string& name );
    
    /** \brief	Renames this tool.
      *
      * \since  1.5
      */
    void setName( const QString& name );

    /** \brief  Sets an offset of this tool's origin in it's local coordinate
      *         system.
      *
      * \since  1.5
      *
      * \see    \ref getOffset, \ref getOrientation
      */
    void setOffset( const Vector& offset );


private:

    std::string name;

    Vector offset;


signals:

    /** \brief	This tool has been renamed.
      */
    void renamed();

    /** \brief	This tool has been renamed.
      */
    void renamed( const std::string& newName );

    /** \brief	This tool has been renamed.
      *
      * \since  1.5
      */
    void renamed( const QString& newName );

    /** \brief  Emitted after the offset of this tool's origin in it's local
      *         coordinate system has changed.
      *
      * \since  1.5
      */
    void offsetChanged();

    /** \brief  Emitted after the offset of this tool's origin in it's local
      *         coordinate system has changed.
      *
      * \since  1.5
      */
    void offsetChanged( const Vector& offset );

}; // Tool



}  // namespace CRA

#endif // TOOL_H_2521354512
