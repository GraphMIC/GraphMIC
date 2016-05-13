#include "gmAppContextBase.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace App
    {
        namespace Context
        {
            Base::Base(const QString& name) : m_visible(false), m_name(name)
            {
                log_trace(Log::New, this << " " << name.toStdString());
            }
            
            auto Base::setVisible(bool flag) -> void
            {
                log_trace(Log::Set, flag);
                
                if (this->m_visible != flag)
                {
                    this->m_visible = flag;
                    emit this->visibleChanged();
                }
            }
            
            auto Base::getName() -> QString
            {
                return this->m_name;
            }
            
            auto Base::getVisible() -> bool
            {
                return this->m_visible;
            }
            
            Base::~Base()
            {
                log_trace(Log::Del, this);
            }
        }
    }
}