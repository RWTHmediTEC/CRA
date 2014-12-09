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

#ifndef DEFAULTLOCALIZER_H_2521354512
#define DEFAULTLOCALIZER_H_2521354512

#include "cra_global.h"
#include "Localizer.h"

namespace CRA
{



// ----------------------------------------------------------------------------------
// DefaultLocalizer
// ----------------------------------------------------------------------------------

/** \brief  CLocalizer based implementation of the Localizer interface.
  *
  * \author Leonid Kostrykin
  * \date   23.3.12 - 28.3.12
  */
class CRA_EXPORT DefaultLocalizer : public Localizer
{

public:

    /** \brief	Lists possible object states.
      */
    enum State
    {
        ready,  ///< \brief  The underlying CLocalizer is tracking.
        asleep  ///< \brief  The underlying CLocalizer is not tracking.
    };


    /** \brief	Thrown when an INI file with an illegal format is provided.
      */
    struct illegalIniFile {};
    
    /** \brief	Thrown when an non-existent INI file is provided.
      */
    struct missingIniFile {};


    /** \brief	Instantiates.
      *
      * Initializes the underlying CLocalizer.
      *
      * \throws illegalIniFile when the provided INI file has an illegal format.
      * \throws missingIniFile when the provided INI file does not exist.
      */
    DefaultLocalizer( const std::string& iniFile );

    /** \brief	Shuts down the underlying CLocalizer.
      */
    virtual ~DefaultLocalizer();


    virtual bool fetch( const std::string& port, Transformation& out );


    /** \brief	Ensures a certain object state as far as possible.
      *
      * Usually there is no need for requesting the object state manually.
      */
    void requestState( State );


    /** \brief	Reinitializes the underlying CLocalizer.
      *
      * \throws illegalIniFile when the provided INI file has an illegal format.
      * \throws missingIniFile when the provided INI file does not exist.
      */
    void loadFromIni( const std::string& iniFile );


private:

    class Details;

    const std::unique_ptr< Details > pimpl;

}; // DefaultLocalizer



}  // namespace CRA

#endif // DEFAULTLOCALIZER_H_2521354512
