#include "gmPythonNodeDesigner.hpp"
#include "gmPythonNodeObject.hpp"
#include "gmPythonNodeNumber.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            Designer* Designer::instance = nullptr;

            Designer::Designer()
            {
                if (instance)
                {
                    throw new std::runtime_error("instance already existing");
                }

                instance = this;
            }

            auto Designer::Create() -> Designer*
            {
                return new Designer();
            }

            auto Designer::setNode(Object* node) -> void
            {
                this->m_node = node;
                emit this->nodeChanged();
            }
            
            auto Designer::getNode() -> Object*
            {
                return this->m_node;
            }
        }
    }
}