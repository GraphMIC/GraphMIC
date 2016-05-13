#include "gmPythonNodeDir.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            Dir::Dir(Object* node) : Param(gm::Component::Type::Dir, node)
            {
                this->setName("directory picker");
            }

            auto Dir::setTitle(const QString& title) -> void
            {
                this->m_title = title;
                emit this->titleChanged();
            }

            auto Dir::getTitle() -> QString
            {
                return this->m_title;
            }
        }
    }
}
