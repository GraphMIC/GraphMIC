#include "gmParamGroup.hpp"
#include "gmParamBase.hpp"
#include "gmParamList.hpp"

#include "gmLog.hpp"
#include "gmAsync.hpp"

namespace gm
{
    namespace Param
    {
        Group::Group(const QString& name) : m_name(name), m_size(0)
        {
            log_trace(Log::New, this);
            
            this->m_paramList   = new List();
            this->m_expanded    = true;
        }
        
        auto Group::setExpanded(bool expanded) -> void
        {
            log_trace(Log::Set, expanded);
            
            if (this->m_expanded != expanded)
            {
                this->m_expanded = expanded;
                emit this->expandedChanged();
            }
        }
        
        auto Group::toggleExpansion() -> void
        {
            log_trace(Log::Func);
            
            setExpanded(!this->m_expanded);
        }
        
        auto Group::getExpanded() -> bool
        {
            log_trace(Log::Get);
            
            return this->m_expanded;
        }
        
        auto Group::getParamList() -> List*
        {
            return this->m_paramList;
        }
        
        auto Group::getParam(const QString& key) -> Base*
        {
            return this->m_paramMap[key];
        }
        
        auto Group::getName() -> QString
        {
            return this->m_name;
        }
        
        auto Group::addParam(Base* param) -> void
        {
            log_trace(Log::Func);
            
            auto key = param->getName();
            
            this->m_paramList->addParam(param);
            this->m_paramMap[key] = param;

            ++this->m_size;
            emit this->sizeChanged();
        }
        
        auto Group::removeParam(const QString& key) -> void
        {
            log_trace(Log::Func);
            
            auto param = this->m_paramMap[key];
            this->m_paramList->removeParam(param);
            this->m_paramMap.remove(key);
            
            -- this->m_size;
            emit this->sizeChanged();
        }
        
        auto Group::getSize() -> int
        {
            return this->m_size;
        }

        auto Group::moveToMain() -> void
        {
            this->m_paramList->moveToMain();
            Async::MoveToMain(this);
        }
        
        Group::~Group()
        {
            log_trace(Log::Del, this);
            
            delete this->m_paramList;
        }
    }
}