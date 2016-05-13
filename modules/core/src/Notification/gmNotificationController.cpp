#include "gmNotificationController.hpp"
#include "gmNotificationEntry.hpp"
#include "gmNotificationList.hpp"

#include "gmNodeObject.hpp"

#include "gmLog.hpp"
#include "gmAsync.hpp"

#include <QTimer>

namespace gm
{
    namespace Notification
    {
        Controller* Controller::instance = nullptr;
        
        Controller::Controller() : m_entries(new List()), m_visible(true)
        {
            if (instance)
            {
                throw "instance already existing";
            }
            
            instance = this;
        }
        
        auto Controller::Create() -> Controller*
        {
            return new Controller();
        }
        
        auto Controller::getEntries() -> List*
        {
            return this->m_entries;
        }
        
        auto Controller::post(const QString& message) -> void
        {
            log_trace(Log::Func);

            Controller::Post(Type::Warning, message);
        }
        
        auto Controller::Post(Type type, const QString& info, Node::Object* node) -> void
        {
            Async::Synchronize([type, info, node](){
                log_trace(Log::Func);

                auto entry = new Entry();

                entry->m_type       = type;
                entry->m_info       = info;
                entry->m_node       = node;

                if (node)
                {
                    entry->m_info.prepend("Node \'" + node->getName() + "\': ");
                    node->addNotification(entry);
                }
                else
                {
                    QTimer::singleShot(10000, entry, SLOT(destroy()));
                }
                switch (type)
                {
                    case Type::Warning: entry->m_title     = "Warning"; break;
                    case Type::Error: entry->m_title       = "Error"; break;
                    case Type::Info: entry->m_title        = "Info"; break;
                }

                instance->m_entries->addEntry(entry);
                
                if (!instance->m_visible)
                {
                    instance->m_visible = true;
                    emit instance->visibleChanged();
                }
            });
        }

        auto Controller::clear() -> void
        {
            this->m_entries->clear();
        }
        
        auto Controller::setVisible(bool visible) -> void
        {
            log_trace(Log::Set, visible);
            
            if (this->m_visible != visible)
            {
                this->m_visible = visible;
                emit this->visibleChanged();
            }
        }
        
        auto Controller::isVisible() -> bool
        {
            return this->m_visible;
        }
        
        auto Controller::show() -> void
        {
            this->m_visible = true;
            emit this->visibleChanged();
        }

        Controller::~Controller()
        {
            log_trace(Log::Del, this);
        }
    }
}
