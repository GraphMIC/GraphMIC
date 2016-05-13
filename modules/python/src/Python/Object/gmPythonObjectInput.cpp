#include "gmPythonObjectInput.hpp"
#include "gmLogicBase.hpp"
#include "gmPythonObjectImage.hpp"

namespace gm
{
    namespace Python
    {
        namespace Object
        {
            using namespace boost::numpy;
            using namespace boost::python;

            Input::Input():
            m_vector(new std::array<double, 4>)
            {
            }

            Input::~Input()
            {
                delete m_vector;
            }

            auto Input::setNode(gm::Node::Object* node) -> void
            {
                this->m_node = node;
            }

            auto Input::getImage(std::string id, unsigned int index) -> Image*
            {
                Image* pyImage = new Image();

                mitk::Image::Pointer mitkImage = this->m_node->getLogic()->getInput<Data::Image>(QString::fromStdString(id))->getImage(index)->getMitkImage();

                pyImage->setImage(mitkImage);
                pyImage->generateAll();

                return pyImage;
            }

            auto Input::getVector(std::string id, unsigned int index) -> boost::numpy::ndarray
            {
                auto arr = this->m_node->getLogic()->getInput<Data::Vector>(QString::fromStdString(id))->getVector(index)->getValues();

                m_vector->swap(arr);

                return from_data(m_vector, dtype::get_builtin<double>(), make_tuple(arr.size()), make_tuple(sizeof(double)), object());
            }

            auto Input::getNumber(std::string id, unsigned int index) -> double
            {
                 return this->m_node->getLogic()->getInput<Data::Number>(QString::fromStdString(id))->getNumber(index)->getValue();
            }
        }
    }
}
