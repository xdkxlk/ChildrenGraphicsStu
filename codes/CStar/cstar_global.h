#ifndef CSTAR_GLOBAL_H
#define CSTAR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CSTAR_LIBRARY)
#  define CSTARSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CSTARSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CSTAR_GLOBAL_H
