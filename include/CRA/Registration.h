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

#ifndef REGISTRATION_H_2521354512
#define REGISTRATION_H_2521354512

#include "cra_global.h"
#include "Transformation.h"
#include <set>
#include <memory>
#include <QObject>

namespace CRA
{

class Tool;
class Link;



// ----------------------------------------------------------------------------------
// Registration
// ----------------------------------------------------------------------------------

/** \brief	Represents a registration.
  *
  * \attention
  * The \ref setTransformation "transformation" must be performed to the scene space
  * in millimeters, \em not in model units.
  *
  * \author Leonid Kostrykin
  * \date   23.3.12 - 17.8.12
  */
class CRA_EXPORT Registration : public QObject
{

    Q_OBJECT

public:

    /** \brief	Creates new registration for given reference base.
      */
    Registration( Tool& referenceBase );

    /** \brief	Releases acquired resources.
      */
    ~Registration();


    /** \brief	Associates another reference base.
      */
    void setReferenceBase( Tool& );

    /** \brief	References the associated reference base.
      */
    Tool& getReferenceBase() const;


    /** \brief	Sets the matrix which transforms from the reference base's space to scene space.
      *
      * The supplied transformation is expected to map coordinates from reference base's local
      * space to the scene space in millimeters, \em not in model units.
      *
      * Emits the \ref transformationChanged signal.
      */
    void setTransformation( const Transformation& );

    /** \brief	Tells the current transformation matrix of this registration.
      */
    const Transformation& getTransformation() const;


    /** \brief	Overwrites the translation vector of the previously supplied transformation matrix.
      *
      * The translation vector must be given in \em millimeters.
      *
      * \post   <code>hasCustomTranslation() == true</code>
      *
      * Emits the \ref transformationChanged signal.
      *
      * \see    \ref removeCustomTranslation, \ref hasCustomTranslation, \ref getCustomTranslation
      * \since  1.7
      */
    void setCustomTranslation( const Vector& );

    /** \brief	Resets this registration's transformation to the originally supplied translation vector.
      *
      * \post   <code>hasCustomTranslation() == false</code>
      *
      * Emits the \ref transformationChanged signal.
      *
      * \see    \ref setCustomTranslation, \ref hasCustomTranslation, \ref getCustomTranslation
      */
    void removeCustomTranslation();

    /** \brief	Tells the currently set custom translation vector.
      *
      * \pre    <code>hasCustomTranslation() == true</code>
      *
      * \see    \ref setCustomTranslation, \ref removeCustomTranslation, \ref hasCustomTranslation
      * \since  1.7
      */
    const Vector& getCustomTranslation() const;

    /** \brief	Tells whether a custom translation vector is being used or the original one.
      *
      * \see    \ref setCustomTranslation, \ref removeCustomTranslation, \ref getCustomTranslation
      */
    bool hasCustomTranslation() const;


    /** \brief	Links a tool with a virtual scene element.
      *
      * The linked virtual scene element gets moved when it's physical representation's
      * position changes.
      */
    void add( const Link& );

    /** \brief	Releases the link of a tool and a virtual scene element.
      */
    void remove( const Link& );

    /** \brief	Tells all existing links.
      */
    const std::set< Link >& getLinks() const
    {
        return links;
    }


    /** \brief	Updates the linked virtual scene elements.
      *
      * For each linked virtual scene element, it's \f$ T \f$-transformed bearing to the
      * reference base is passed to it's \ref VirtualElement::update method. \f$ T \f$
      * is the current transformation matrix, which is returned by \ref getTransformation.
      */
    void updateVirtualElements();


signals:

    /** \brief	Emitted whenever the transformation matrix changes.
      */
    void transformationChanged();
    
    /** \brief	Emitted whenever the transformation matrix changes.
      */
    void transformationChanged( const Transformation& );


private slots:

    void applyCustomTranslation();

    
private:

    Tool* referenceBase;

    Transformation transformation;

    Vector originalTranslation;

    std::set< Link > links;

    std::unique_ptr< Vector > customTranslation;

}; // Registration



}  // namespace CRA

#endif // REGISTRATION_H_2521354512
