#include <QApplication>

#include "gmLog.hpp"

#include "gmApp.hpp"

#include "gmAppMenu.hpp"
#include "gmModuleController.hpp"
#include "gmAppController.hpp"

namespace gm
{
    Application* Application::instance = nullptr;
    
    Application::Application() : m_view(nullptr)
    {
        gm::Module::Controller::Create();
        
        if (instance)
        {
            throw "instance already existing";
        }
        
        instance = this;
    }

    auto Application::setOrgName(const QString& orgName) -> void
    {
        this->m_orgName = orgName;
    }
    
    auto Application::setOrgDomain(const QString& orgDomain) -> void
    {
        this->m_orgDomain = orgDomain;
    }
    
    auto Application::setAppName(const QString& appName) -> void
    {
        this->m_appName = appName;
    }
    
    auto Application::setResourceFile(const QString& resourceFile) -> void
    {
        this->m_resourceFile = resourceFile;
    }
    
    auto Application::setVersionString(const QString& versionString) -> void
    {
        this->m_versionString = versionString;
    }
    
    auto Application::getView() -> QQuickView*
    {
        return this->m_view;
    }
    
    auto Application::getResourceDir() -> QString
    {
        return this->m_resourceDir;
    }
    
    auto Application::getClipboard() -> QClipboard*
    {
        return QApplication::clipboard();
    }
    
    auto Application::exec(int argc, char** argv) -> int
    {
        QApplication::setOrganizationName(this->m_orgName);
        QApplication::setOrganizationDomain(this->m_orgDomain);
        QApplication::setApplicationName(this->m_appName);
        QApplication::setApplicationVersion(this->m_versionString);
        QApplication::setStartDragDistance(0);
        QApplication::setStartDragTime(0);
        
        QApplication application(argc, argv);
        
        auto path = QDir(QGuiApplication::applicationDirPath());
        path.cdUp();
        
        this->m_resourceDir = path.absolutePath() + "/Resources";
        
        auto menu = App::Menu::Create();
        menu->init();
        
        auto controller = App::Controller::Create();
        controller->setVersion(this->m_versionString);
        
        qmlRegisterSingletonType<gm::App::Controller>("org.graphmic.app", 1, 0, "instance", gm::App::Controller::InstanceProvider);
        
        this->m_view = new QQuickView();
        this->m_view->setTitle(this->m_appName);
        this->m_view->engine()->addImportPath(path.absolutePath() + "/Modules");
        this->m_view->engine()->rootContext()->setContextProperty("Module", Module::Controller::instance);
        this->m_view->setSource(QUrl::fromLocalFile(this->m_resourceDir + this->m_resourceFile));
        this->m_view->setResizeMode(QQuickView::SizeRootObjectToView);
        this->m_view->showMaximized();
        
        return application.exec();
    }
    
}
