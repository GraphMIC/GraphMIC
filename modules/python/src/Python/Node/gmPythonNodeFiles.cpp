#include "gmPythonNodeFiles.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            Files::Files(Object* node) : Param(gm::Component::Type::Files, node)
            {
                this->setName("File Loader");
                this->m_title = "Load Files";
                this->m_filter = "*.*";
            }

            auto Files::setTitle(const QString& title) -> void
            {
                this->m_title = title;
                emit this->titleChanged();
            }

            auto Files::getTitle() -> QString
            {
                return this->m_title;
            }

            auto Files::setFilter(const QString& filter) -> void
            {
                this->m_filter = filter;
                emit this->filterChanged();
            }

            auto Files::getFilter() -> QString
            {
                return this->m_filter;
            }
        }
    }
}
