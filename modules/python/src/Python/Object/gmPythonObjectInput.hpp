#pragma once
#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include "gmNodeObject.hpp"
#include "gmPythonObjectImage.hpp"

namespace gm
{
    namespace Python
    {
        namespace Object
        {
            class Input
            {
            private:
                gm::Node::Object*       m_node;
                std::array<double, 4>*  m_vector;
            public:
                Input();
                ~Input();
                auto setNode(gm::Node::Object* node) -> void;
                auto getImage(std::string id, unsigned int index) -> Image*;
                auto getVector(std::string id, unsigned int index) -> boost::numpy::ndarray;
                auto getNumber(std::string id, unsigned int index) -> double;
            };
        }
    }
}