#include "gmPythonObjectNode.hpp"
#include "gmPythonObjectParam.hpp"
#include "gmPythonObjectInput.hpp"
#include "gmPythonObjectOutput.hpp"

#include "gmNodeObject.hpp"

namespace gm
{
    namespace Python
    {
        namespace Object
        {
            Node::Node():
            m_param(new Param),
            m_input(new Input),
            m_output(new Output)
            {
            }

            Node::~Node()
            {
                delete m_param;
                delete m_input;
                delete m_output;
            }

            auto Node::setNode(gm::Node::Object* node) -> void
            {
                this->m_node = node;
            }

            auto Node::getParam() -> Param*
            {
                this->m_param->setNode(this->m_node);
                return this->m_param;
            }

            auto Node::getInput() -> Input*
            {
                this->m_input->setNode(this->m_node);
                return this->m_input;
            }

            auto Node::getOutput() -> Output*
            {
                this->m_output->setNode(this->m_node);
                return this->m_output;
            }
        }
    }
}