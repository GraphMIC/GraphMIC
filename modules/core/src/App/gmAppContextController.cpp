#include "gmAppContextController.hpp"

#include "gmAppSidebar.hpp"

#include "gmAppContextGraph.hpp"
#include "gmAppContextPython.hpp"
#include "gmAppContextViewer.hpp"
#include "gmAppContextSettings.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace App
    {
        namespace Context
        {
            Controller* Controller::instance = nullptr;
            
            Controller::Controller() : m_activeContext(nullptr)
            {
                log_trace(Log::New, this);
                
                if (instance)
                {
                    throw "instance already existing";
                }
                
                instance = this;
            }
            
            auto Controller::init() -> void
            {
                log_trace(Log::Func);
                
                Graph::Create();
                Python::Create();
                Settings::Create();
                Viewer::Create();
                
                setActiveContext(Graph::instance);
            }
            
            auto Controller::getGraph() -> Graph*
            {
                log_trace(Log::Get, Graph::instance);
                
                return Graph::instance;
            }
            
            auto Controller::getPython() -> Python*
            {
                return Python::instance;
            }
            
            auto Controller::getViewer() -> Viewer*
            {
                return Viewer::instance;
            }
            
            auto Controller::getSettings() -> Settings*
            {
                return Settings::instance;
            }
            
            auto Controller::setGraphContext() -> void
            {
                log_trace(Log::Func);
                
                this->setActiveContext(Graph::instance);
            }
            
            auto Controller::setPythonContext() -> void
            {
                log_trace(Log::Func);
                
                this->setActiveContext(Python::instance);
            }
            
            auto Controller::setViewerContext() -> void
            {
                log_trace(Log::Func);
                
                setActiveContext(Viewer::instance);
            }
            
            auto Controller::setSettingsContext() -> void
            {
                log_trace(Log::Func);
                
                setActiveContext(Settings::instance);
            }
            
            auto Controller::Create() -> Controller*
            {
                log_trace(Log::Func);
                
                return new Controller();
            }
            
            auto Controller::setActiveContext(Base* context) -> void
            {
                log_trace(Log::Set, context);
                
                if (this->m_activeContext != context)
                {
                    if (this->m_activeContext)
                    {
                        this->m_activeContext->setVisible(false);
                    }
                    
                    if (context)
                    {
                        context->setVisible(true);
                    }
                    
                    this->m_activeContext = context;
                    emit this->activeContextChanged();
                }
            }
            
            auto Controller::getActiveContext() -> Base*
            {
                log_trace(Log::Get);
                
                return this->m_activeContext;
            }
            
            Controller::~Controller()
            {
                log_trace(Log::Del, this);
                
                instance = nullptr;
            }
        }
    }
}