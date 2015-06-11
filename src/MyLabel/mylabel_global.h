#ifndef MYLABEL_GLOBAL_H
#define MYLABEL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MYLABEL_LIB
# define MYLABEL_EXPORT Q_DECL_EXPORT
#else
# define MYLABEL_EXPORT Q_DECL_IMPORT
#endif

#endif // MYLABEL_GLOBAL_H
