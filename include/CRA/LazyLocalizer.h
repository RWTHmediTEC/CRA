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

#ifndef LAZYLOCALIZER_H_2521354512
#define LAZYLOCALIZER_H_2521354512

#include "cra_global.h"
#include "Localizer.h"
#include <map>
#include <QTime>

namespace CRA
{



// ----------------------------------------------------------------------------------
// LazyLocalizer
// ----------------------------------------------------------------------------------

/** \brief	Lazy proxy implementation of the Localizer interface.
  *
  * Results returned by the referenced Localizer implementation are cached. Queries
  * for cached data are processed without querying the referenced implementation,
  * unless the cache was invalidated. The cache is invalidated when it's last update
  * becomes too old.
  *
  * \author Leonid Kostrykin
  * \date   23.3.12 - 28.3.12
  */
class CRA_EXPORT LazyLocalizer : public Localizer
{

public:

    /** \brief	Holds the default number of milliseconds spent before the cache is invalidated.
      */
    const static unsigned int defaultLazynessThreshold;


    /** \brief	Instantiates.
      */
    LazyLocalizer( Localizer& service );


    virtual bool fetch( const std::string& port, Transformation& out );


    /** \brief	Defines the timeout of cache invalidation.
      *
      * \param  lazynessThreshold   timeout in milliseconds
      */
    void setLazynessThreshold( unsigned int lazynessThreshold )
    {
        this->lazynessThreshold = lazynessThreshold;
    }

    
    /** \brief	Tells the timeout of cache invalidation.
      *
      * \return timeout in milliseconds
      */
    unsigned int getLazynessThreshold() const
    {
        return lazynessThreshold;
    }


private:

    Localizer& service;


    typedef std::map< std::string, QTime > StringToTime;

    typedef std::map< std::string, Transformation > StringToTransformation;

    typedef std::map< std::string, bool > StringToBoolean;


    StringToTime cacheCurrentness;

    StringToTransformation orientationCache;

    StringToBoolean visibilityCache;


    unsigned int lazynessThreshold;

}; // LazyLocalizer



}  // namespace CRA

#endif // LAZYLOCALIZER_H_2521354512
