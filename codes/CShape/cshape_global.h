#ifndef CSHAPE_GLOBAL_H
#define CSHAPE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CSHAPE_LIBRARY)
#  define CSHAPESHARED_EXPORT Q_DECL_EXPORT
#else
#  define CSHAPESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CSHAPE_GLOBAL_H
