#include "gmDialogBase.hpp"

#include "gmApp.hpp"
#include "gmAppController.hpp"

#include "gmModuleController.hpp"

namespace gm
{
    namespace Dialog
    {
        Base::Base(QString name)
        {
            log_trace(Log::New, this);
            
            this->m_view = new QQuickView();
            this->m_view->engine()->rootContext()->setContextProperty("App", App::Controller::instance);
            this->m_view->engine()->rootContext()->setContextProperty("Dialog", this);
            this->m_view->setSource(Application::instance->getResourceDir() + "/qml/dialog/" + name + ".qml");
            this->m_view->setScreen(Application::instance->getView()->screen());
            this->m_view->setColor("#00000000");
            this->m_view->setTitle(name);
            this->m_view->setFlags(Qt::Tool);
            this->m_view->setResizeMode(QQuickView::SizeRootObjectToView);
            this->m_view->setModality(Qt::ApplicationModal);
            this->m_view->setMinimumHeight(32);
            this->m_view->setMinimumWidth(32);
        }
        
        auto Base::close() -> void
        {
            log_trace(Log::Func);
            
            this->m_view->close();
        }
        
        auto Base::show() -> void
        {
            log_trace(Log::Func);
            
            this->m_view->show();
        }
    }
}
