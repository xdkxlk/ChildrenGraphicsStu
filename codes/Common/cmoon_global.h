#ifndef CMOON_GLOBAL_H
#define CMOON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CMOON_LIBRARY)
#  define CMOONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CMOONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CMOON_GLOBAL_H
