#pragma once
#include <boost/numpy.hpp>
#include <boost/python.hpp>

#include <mitkImage.h>

namespace gm
{
    namespace Python
    {
        namespace Object
        {
            class Image
            {
            private:
                mitk::Image::Pointer m_image;

                boost::python::tuple shape = boost::python::make_tuple(1, 1);
                boost::numpy::dtype dtype  = boost::numpy::dtype::get_builtin<float>();

                boost::numpy::ndarray m_data = boost::numpy::empty(shape, dtype);;
                boost::numpy::ndarray m_dims = boost::numpy::empty(shape, dtype);;
                boost::python::object m_comp = boost::numpy::empty(shape, dtype);;

                boost::numpy::ndarray m_spacing = boost::numpy::empty(shape, dtype);;
                boost::numpy::ndarray m_origin  = boost::numpy::zeros(shape, dtype);;
            public:
                Image();
                ~Image();
                
                auto setImage(mitk::Image::Pointer image) -> void;
                auto getData() -> boost::numpy::ndarray;
                auto getSpacing() -> boost::numpy::ndarray;
                auto getOrigin() -> boost::numpy::ndarray;
                auto getDimensions() -> boost::numpy::ndarray;
                auto getNumberOfComponents() -> boost::python::object;

                auto setData(boost::numpy::ndarray data) -> void;
                auto setSpacing(boost::numpy::ndarray spacing) -> void;
                auto setOrigin(boost::numpy::ndarray origin) -> void;
                auto setDimensions(boost::numpy::ndarray dims) -> void;
                auto setNumberOfComponents(boost::python::object comp) -> void;

                auto generateData() -> void;
                auto generateSpacing() -> void;
                auto generateOrigin() -> void;
                auto generateDimensions() -> void;
                auto generateNumberOfComponents() -> void;
                auto generateAll() -> void;
            };
        }
    }
}