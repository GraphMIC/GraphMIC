#include <QtCore/QtGlobal>

#if defined(GRAPHMIC_LIB_LOGIC)
    #define GM_LOGIC_EXPORT Q_DECL_EXPORT
#else
    #define GM_LOGIC_EXPORT Q_DECL_IMPORT
#endif