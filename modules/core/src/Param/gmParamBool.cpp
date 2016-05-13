#include "gmParamBool.hpp"

namespace gm
{
    namespace Param
    {
        Component::Type Bool::ComponentType = Component::Type::Bool;
        
        Bool::Bool(const QString& name, bool value) : Base(ComponentType, name)
        {
            log_trace(Log::New, this);
            
            this->m_value = value;
        }
        
        Bool::Bool(const QString& name) : Bool(name, false) {}
        
        auto Bool::setValue(bool value) -> void
        {
            log_trace(Log::Set, value);
            
            if (this->m_value != value)
            {
                this->m_value = value;
                emit this->valueChanged();
                this->setModified(true);
            }
        }
        
        auto Bool::getValue() -> bool
        {
            log_trace(Log::Get);
            
            return this->m_value;
        }
        
        Bool::~Bool()
        {
            log_trace(Log::Del, this);
        }
    }
}