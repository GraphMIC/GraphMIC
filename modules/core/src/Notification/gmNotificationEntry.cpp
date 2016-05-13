#include "gmLog.hpp"

#include "gmNotificationList.hpp"
#include "gmNotificationEntry.hpp"
#include "gmNotificationController.hpp"

#include "gmDebugController.hpp"

namespace gm
{
    namespace Notification
    {
        int Entry::instanceCount = 0;
        
        Entry::Entry()
        {
            log_trace(Log::New, this);
        
            Debug::Controller::instance->incNotificationCount();
        }
        
        Entry::Entry(const Entry& other)
        {
            log_trace(Log::New, this);
            
            this->m_type    = other.m_type;
            this->m_info    = other.m_info;
            this->m_title   = other.m_title;
            this->m_node    = other.m_node;
        }
        
        auto Entry::getTitle() -> QString
        {
            log_trace(Log::Get, this);
            
            return this->m_title;
        }
        
        auto Entry::getInfo() -> QString
        {
            log_trace(Log::Get, this);
            
            return this->m_info;
        }
        
        auto Entry::getType() -> Type
        {
            return this->m_type;
        }
        
        auto Entry::getNode() -> Node::Object*
        {
            return this->m_node;
        }
        
        Entry::~Entry()
        {
            log_trace(Log::Del, this);
            
            Debug::Controller::instance->decNotificationCount();
        }
        
        auto Entry::destroy() -> void
        {
            log_trace(Log::Func);
            
            Controller::instance->getEntries()->removeEntry(this);
            delete this;
        }
    }
}
