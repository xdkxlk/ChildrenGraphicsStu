#ifndef CLADDER_GLOBAL_H
#define CLADDER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CLADDER_LIBRARY)
#  define CLADDERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CLADDERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CLADDER_GLOBAL_H
