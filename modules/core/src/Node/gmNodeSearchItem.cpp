#include "gmLog.hpp"
#include "gmNodeSearchItem.hpp"

namespace gm
{
    namespace Node
    {
        SearchItem::SearchItem(const QString& prefix, const QString& name)
        {
            this->m_prefix  = prefix;
            this->m_name    = name;
        }
        
        auto SearchItem::getName() -> QString
        {
            return this->m_name;
        }
        
        auto SearchItem::getPrefix() -> QString
        {            
            return this->m_prefix;
        }

        auto SearchItem::contains(const QString& str) -> bool
        {
            return (this->m_name.contains(str, Qt::CaseInsensitive) || this->m_prefix.contains(str, Qt::CaseInsensitive));
        }

        auto SearchItem::matches(const QString& str) -> bool
        {
            return (this->m_prefix + "::" + this->m_name).compare(str) == 0;
        }
    }
}
