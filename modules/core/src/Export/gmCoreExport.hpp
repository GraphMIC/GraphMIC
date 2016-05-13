#include <QtCore/QtGlobal>

#if defined(GRAPHMIC_LIB_CORE)
    #define GM_CORE_EXPORT Q_DECL_EXPORT
#else
    #define GM_CORE_EXPORT Q_DECL_IMPORT
#endif