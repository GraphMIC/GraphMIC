#include <QtCore/QtGlobal>

#if defined(GRAPHMIC_LIB_PREVIEW)
    #define GM_PREVIEW_EXPORT Q_DECL_EXPORT
#else
    #define GM_PREVIEW_EXPORT Q_DECL_IMPORT
#endif
