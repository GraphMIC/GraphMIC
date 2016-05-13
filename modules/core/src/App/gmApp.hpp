#pragma once

#include "gmCoreExport.hpp"

#include <QtGlobal>
#include <QQuickView>

namespace gm
{
    class GM_CORE_EXPORT Application : public QObject
    {
    private:
        QQuickView* m_view;
        QString m_versionString;
        QString m_resourceDir;
        QString m_resourceFile;
        QString m_orgName;
        QString m_orgDomain;
        QString m_appName;
    public:
        static Application* instance;
        static auto getClipboard() -> QClipboard*;
        Application();
        auto setVersionString(const QString&) -> void;
        auto setResourceFile(const QString&) -> void;
        auto setOrgName(const QString&) -> void;
        auto setOrgDomain(const QString&) -> void;
        auto setAppName(const QString&) -> void;
        auto getView() -> QQuickView*;
        auto getResourceDir() -> QString;
        auto exec(int, char**) -> int;
        
        template <class TModule>
        auto use() -> void
        {
            TModule::Initialize();
        }
    };
}