#include "gmPythonObjectImage.hpp"

#include <mitkImage.h>
#include <mitkPixelType.h>
#include <mitkImageReadAccessor.h>

namespace gm
{
    namespace Python
    {
        namespace Object
        {
            using namespace boost::python;
            using namespace boost::numpy;

            Image::Image()
            {
            }

            Image::~Image()
            {
            }

            auto Image::setImage(mitk::Image::Pointer image) -> void
            {
                this->m_image = image;
            }

            auto Image::setNumberOfComponents(boost::python::object comp) -> void
            {
                this->m_comp = comp;
            }

            auto Image::setData(boost::numpy::ndarray data) -> void
            {
                this->m_data = data;
            }

            auto Image::setDimensions(boost::numpy::ndarray dims) -> void
            {
                this->m_dims = dims;
            }

            auto Image::setOrigin(boost::numpy::ndarray origin) -> void
            {
                this->m_origin = origin;
            }

            auto Image::setSpacing(boost::numpy::ndarray spacing) -> void
            {
                this->m_spacing = spacing;
            }

            auto Image::getNumberOfComponents() -> boost::python::object
            {
                return this->m_comp;
            }

            auto Image::getSpacing() -> boost::numpy::ndarray
            {
                return this->m_spacing;
            }

            auto Image::getOrigin() -> boost::numpy::ndarray
            {
                return this->m_origin;
            }

            auto Image::getData() -> boost::numpy::ndarray
            {
                return this->m_data;
            }

            auto Image::getDimensions() -> boost::numpy::ndarray
            {
                return this->m_dims;
            }

            auto Image::generateData() -> void
            {
                unsigned int* dimensions = this->m_image->GetDimensions();
                unsigned int dimension = this->m_image->GetDimension();

                mitk::PixelType pixelType = this->m_image->GetPixelType();

                mitk::ImageReadAccessor racc(this->m_image);
                void* array = (void*) racc.GetData();

                boost::numpy::dtype py_dtype = boost::numpy::dtype::get_builtin<short>();
                int py_size = sizeof(short);

                if( pixelType.GetComponentType() == itk::ImageIOBase::DOUBLE ) {
                    py_dtype = boost::numpy::dtype::get_builtin<double>();
                    py_size = sizeof(double);
                } else if( pixelType.GetComponentType() == itk::ImageIOBase::FLOAT ) {
                    py_dtype = boost::numpy::dtype::get_builtin<float>();
                    py_size = sizeof(float);
                } else if( pixelType.GetComponentType() == itk::ImageIOBase::SHORT) {
                    py_dtype = boost::numpy::dtype::get_builtin<short>();
                    py_size = sizeof(short);
                } else if( pixelType.GetComponentType() == itk::ImageIOBase::CHAR ) {
                    py_dtype = boost::numpy::dtype::get_builtin<char>();
                    py_size = sizeof(char);
                } else if( pixelType.GetComponentType() == itk::ImageIOBase::INT ) {
                    py_dtype = boost::numpy::dtype::get_builtin<int>();
                    py_size = sizeof(int);
                } else if( pixelType.GetComponentType() == itk::ImageIOBase::LONG ) {
                    py_dtype = boost::numpy::dtype::get_builtin<long>();
                    py_size = sizeof(long);
                } else if( pixelType.GetComponentType() == itk::ImageIOBase::UCHAR ) {
                    py_dtype = boost::numpy::dtype::get_builtin<unsigned char>();
                    py_size = sizeof(unsigned char);
                } else if( pixelType.GetComponentType() == itk::ImageIOBase::UINT ) {
                    py_dtype = boost::numpy::dtype::get_builtin<unsigned int>();
                    py_size = sizeof(unsigned int);
                } else if( pixelType.GetComponentType() == itk::ImageIOBase::ULONG ) {
                    py_dtype = boost::numpy::dtype::get_builtin<unsigned long>();
                    py_size = sizeof(unsigned long);
                } else if( pixelType.GetComponentType() == itk::ImageIOBase::USHORT ) {
                    py_dtype = boost::numpy::dtype::get_builtin<unsigned short>();
                    py_size = sizeof(unsigned short);
                }

                unsigned int py_dimension = dimension;

                if(pixelType.GetNumberOfComponents() > 1)
                    py_dimension += 1;

                    std::vector<unsigned int> py_shape(py_dimension);
                    std::vector<unsigned int> py_stride(py_dimension);

                    for (int i = 0; i < dimension; i++) {
                        py_shape[i] = dimensions[dimension-1-i];
                    }


                if(pixelType.GetNumberOfComponents() > 1)
                {
                    py_shape[py_dimension-1] = pixelType.GetNumberOfComponents();

                    if(dimension == 2)
                    {
                        py_stride[2] = py_size;
                        py_stride[1] = py_size*pixelType.GetNumberOfComponents();
                        py_stride[0] = py_stride[1]*dimensions[0];
                    }
                    else
                    {
                        py_stride[3] = py_size;
                        py_stride[2] = py_size*pixelType.GetNumberOfComponents();
                        py_stride[1] = py_stride[2] * dimensions[0];
                        py_stride[0] = py_stride[1] * dimensions[1];
                    }
                }
                else
                {
                    if(dimension == 2)
                    {
                        py_stride[1] = py_size;
                        py_stride[0] = py_stride[1]*dimensions[0];
                    }
                    else
                    {
                        py_stride[2] = py_size;
                        py_stride[1] = py_stride[2] * dimensions[0];
                        py_stride[0] = py_stride[1] * dimensions[1];
                    }
                }

                this->m_data = boost::numpy::from_data<std::vector<unsigned int>>(array, py_dtype, py_shape, py_stride, boost::python::object());
            }

            auto Image::generateSpacing() -> void
            {
                const mitk::Vector3D spacing = this->m_image->GetGeometry()->GetSpacing();

                Py_intptr_t shape[1] = { 3 };
                boost::numpy::ndarray array = boost::numpy::zeros(1, shape, boost::numpy::dtype::get_builtin<double>());

                array[0] = spacing[0];
                array[1] = spacing[1];
                array[2] = spacing[2];

                this->m_spacing = array;

            }

            auto Image::generateOrigin() -> void
            {
                const mitk::Point3D origin = this->m_image->GetGeometry()->GetOrigin();

                Py_intptr_t shape[1] = { 3 };
                boost::numpy::ndarray array = boost::numpy::zeros(1, shape, boost::numpy::dtype::get_builtin<double>());

                array[0] = origin[0];
                array[1] = origin[1];
                array[2] = origin[2];

                this->m_origin = array;
            }

            auto Image::generateDimensions() -> void
            {
                unsigned int* imgDim = this->m_image->GetDimensions();
                this->m_dims = from_data(imgDim, dtype::get_builtin<unsigned int>(), make_tuple(3), make_tuple(sizeof(unsigned int)), object());
            }

            auto Image::generateNumberOfComponents() -> void
            {
                this->m_comp = object(this->m_image->GetPixelType().GetNumberOfComponents());
            }
            
            auto Image::generateAll() -> void
            {
                this->generateSpacing();
                this->generateOrigin();
                this->generateDimensions();
                this->generateNumberOfComponents();
                this->generateData();
            }
        }
    }
}