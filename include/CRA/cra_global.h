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

#ifndef CRA_GLOBAL_H
#define CRA_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef CRA_LIB
# define CRA_EXPORT Q_DECL_EXPORT
#else
# define CRA_EXPORT Q_DECL_IMPORT
#endif

#endif // CRA_GLOBAL_H
