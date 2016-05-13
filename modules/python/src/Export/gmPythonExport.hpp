#include <QtCore/QtGlobal>

#if defined(GRAPHMIC_LIB_PYTHON)
    #define GM_PYTHON_EXPORT Q_DECL_EXPORT
#else
    #define GM_PYTHON_EXPORT Q_DECL_IMPORT
#endif
