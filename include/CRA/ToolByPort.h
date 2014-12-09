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

#ifndef TOOLBYPORT_H_2521354512
#define TOOLBYPORT_H_2521354512

#include "Tool.h"

namespace CRA
{

class Localizer;



// ----------------------------------------------------------------------------------
// ToolByPort
// ----------------------------------------------------------------------------------

/** \brief	\ref Tool implementation which queries the \ref Localizer interface for
  *         it's bearing, using some associated port.
  *
  * \author Leonid Kostrykin
  * \date   23.3.12 - 22.2.13
  */
class CRA_EXPORT ToolByPort : public Tool
{

public:

    /** \brief	Instantiates.
      */
    ToolByPort( Localizer& localizer, const std::string& port, const std::string& name );

    /** \brief	Instantiates.
      */
    ToolByPort( Localizer& localizer, const std::string& port );


    virtual const Transformation& getOrientation() const override;

    virtual bool isVisible() const override;


    /** \brief	Tells the associated port.
      */
    const std::string& getPort() const
    {
        return port;
    }


private:

    Localizer& localizer;

    const std::string port;


    mutable Transformation orientation;

    mutable bool visible;


    void updateFromLocalizer() const;

}; // ToolByPort



}  // namespace CRA

#endif // TOOLBYPORT_H_2521354512
