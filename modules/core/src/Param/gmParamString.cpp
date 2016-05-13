#include "gmParamString.hpp"

#include <QJsonObject>

namespace gm
{
    namespace Param
    {
        Component::Type String::ComponentType = Component::Type::String;
        
        String::String(const QString& name, const QString& value, const QString& regex) : Base(ComponentType, name), m_valid(true), m_value(value), m_regex(regex)
        {
            log_trace(Log::New, this);
        }
        
        String::String(const QString& name) : String(name, "", "") {}
        
        auto String::setRegex(const QString& regex) -> void
        {
            log_trace(Log::Set, regex.toStdString());
            
            this->m_regex = regex;
        }
        
        auto String::getRegex() -> QString
        {
            log_trace(Log::Get);
            
            return this->m_regex;
        }
        
        auto String::setValid(bool valid) -> void
        {
            log_trace(Log::Set, valid);
            
            if (this->m_valid != valid)
            {
                this->m_valid = valid;
                emit this->validChanged();
            }
        }
        
        auto String::getValid() -> bool
        {
            log_trace(Log::Get);
            return this->m_valid;
        }
        
        auto String::setValue(const QString& value) -> void
        {
            log_trace(Log::Set, value.toStdString());
            
            if (this->m_value != value)
            {
                this->m_value = value;
                emit this->valueChanged();
                this->setModified(true);
            
                if (!this->m_regex.isNull())
                {
                    this->setValid(QRegExp(this->m_regex).indexIn(value) > -1);
                }
            }
        }
        
        auto String::getValue() -> QString
        {
            log_trace(Log::Get);
            
            return this->m_value;
        }
        
        String::~String()
        {
            log_trace(Log::Del, this);
        }
    }
}