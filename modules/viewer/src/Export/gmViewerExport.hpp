#include <QtCore/QtGlobal>

#if defined(GRAPHMIC_LIB_VIEWER)
    #define GM_VIEWER_EXPORT Q_DECL_EXPORT
#else
    #define GM_VIEWER_EXPORT Q_DECL_IMPORT
#endif