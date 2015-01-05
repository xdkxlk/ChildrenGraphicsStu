#ifndef CRECT_GLOBAL_H
#define CRECT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CRECT_LIBRARY)
#  define CRECTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CRECTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CRECT_GLOBAL_H
