#ifndef QDHTLIB_GLOBAL_H
#define QDHTLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QDHTLIB_LIBRARY)
#  define QDHTLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QDHTLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QDHTLIB_GLOBAL_H
