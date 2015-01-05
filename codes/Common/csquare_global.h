#ifndef CSQUARE_GLOBAL_H
#define CSQUARE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CSQUARE_LIBRARY)
#  define CSQUARESHARED_EXPORT Q_DECL_EXPORT
#else
#  define CSQUARESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CSQUARE_GLOBAL_H
