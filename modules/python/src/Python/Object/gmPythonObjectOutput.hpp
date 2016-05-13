#pragma once

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include "gmNodeObject.hpp"
#include "gmPythonObjectImage.hpp"

#include <mitkImage.h>

namespace gm
{
    namespace Python
    {
        namespace Object
        {
            class Output
            {
            private:
                gm::Node::Object* m_node;
            public:
                Output();
                ~Output();
                auto setNode(gm::Node::Object* node) -> void;
                auto setImage(std::string id, boost::python::object obj) -> void;
                auto setVector(std::string id, boost::numpy::ndarray) -> void;
                auto setNumber(std::string id, double n) -> void;
                auto generateImage(boost::python::object obj) -> mitk::Image::Pointer;
            };
        }
    }
}