#include "gmParamOption.hpp"

#include <QJsonObject>

namespace gm
{
    namespace Param
    {
        Component::Type Option::ComponentType = Component::Type::Option;
        
        Option::Option(const QString& name, QStringList options, int index) : Base(ComponentType, name)
        {
            log_trace(Log::New, this);
            
            this->m_options = options;
            this->m_index   = index;
        }
        
        Option::Option(const QString& name, QStringList options) : Option(name, options, 0) {}
        
        auto Option::setIndex(int index) -> void
        {
            log_trace(Log::Set, index);
            
            if (this->m_index != index)
            {
                this->m_index = index;
                emit this->indexChanged();
                this->setModified(true);
            }
        }
        
        auto Option::getIndex() -> int
        {
            log_trace(Log::Get);
            
            return this->m_index;
        }
        
        auto Option::setOptions(QStringList options) -> void
        {
            log_trace(Log::Set);
            
            this->m_options = options;
            emit this->optionsChanged();
        }
        
        auto Option::getOptions() -> QStringList
        {
            log_trace(Log::Get);
            
            return this->m_options;
        }
        
        Option::~Option()
        {
            log_trace(Log::Del, this);
        }
    }
}