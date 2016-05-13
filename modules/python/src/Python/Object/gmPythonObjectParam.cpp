#include "gmPythonObjectParam.hpp"
#include "gmNodeObject.hpp"
#include "gmLogicBase.hpp"

namespace gm
{
    namespace Python
    {
        namespace Object
        {
            using namespace boost::numpy;
            using namespace boost::python;

            Param::Param(): m_vector(new std::array<double, 4>)
            {
            }

            Param::~Param()
            {
                delete this->m_vector;
            }

            auto Param::setNode(gm::Node::Object* node) -> void
            {
                this->m_node = node;
            }

            auto Param::getBool(std::string id) -> bool
            {
                return this->m_node->getLogic()->getParam<gm::Param::Bool>(QString::fromStdString(id))->getValue();
            }

            auto Param::getNumber(std::string id) -> double
            {
                return this->m_node->getLogic()->getParam<gm::Param::Number>(QString::fromStdString(id))->getValue();
            }

            auto Param::getString(std::string id) -> QString
            {
                return this->m_node->getLogic()->getParam<gm::Param::String>(QString::fromStdString(id))->getValue();
            }

            auto Param::getOption(std::string id) -> int
            {
                return this->m_node->getLogic()->getParam<gm::Param::Option>(QString::fromStdString(id))->getIndex();
            }

            auto Param::getDir(std::string id) -> QString
            {
                return this->m_node->getLogic()->getParam<gm::Param::Dir>(QString::fromStdString(id))->getDir();
            }

            auto Param::getFiles(std::string id) -> QList<QString>
            {
                return this->m_node->getLogic()->getParam<gm::Param::Files>(QString::fromStdString(id))->getFilePaths();
            }

            auto Param::getVector(std::string id) -> ndarray
            {
                std::array<double, 4> arr = this->m_node->getLogic()->getParam<gm::Param::Vector>(QString::fromStdString(id))->getValues();

                m_vector->swap(arr);

                return from_data(m_vector, dtype::get_builtin<double>(), make_tuple(arr.size()), make_tuple(sizeof(double)), object());
            }
        }
    }
}