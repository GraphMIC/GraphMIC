#include "gmPythonObjectOutput.hpp"
#include "gmLogicBase.hpp"
#include "gmPythonObjectImage.hpp"

#include <mitkIOUtil.h>
#include <mitkPixelType.h>
#include <mitkImageReadAccessor.h>
#include <mitkImageWriteAccessor.h>

namespace gm
{
    namespace Python
    {
        namespace Object
        {
            Output::Output()
            {

            }

            Output::~Output()
            {

            }

            auto Output::setNode(gm::Node::Object* node) -> void
            {
                this->m_node = node;
            }

            auto Output::setImage(std::string id, boost::python::object obj) -> void
            {
                auto output = this->m_node->getLogic()->getOutput<Data::Image>(QString::fromStdString(id));
                auto mitkImage = this->generateImage(obj);
                auto gmImage = new Data::Image(mitkImage);

                output->addImage(gmImage);
            }

            auto Output::setVector(std::string id, boost::numpy::ndarray obj) -> void
            {
                auto output = this->m_node->getLogic()->getOutput<Data::Vector>(QString::fromStdString(id));
                double* ds = reinterpret_cast<double*>(obj.get_data());

                Data::Vector* gmVector;

                if(obj.get_shape()[0] < 4)
                {
                    gmVector = new Data::Vector(ds[0], ds[1], ds[2], 0);
                }
                else
                {
                    gmVector = new Data::Vector(ds[0], ds[1], ds[2], ds[3]);
                }

                output->addVector(gmVector);
            }

            auto Output::setNumber(std::string id, double n) -> void
            {
                auto output = this->m_node->getLogic()->getOutput<Data::Number>(QString::fromStdString(id));
                output->addNumber(new Data::Number(n));
            }

            auto Output::generateImage(boost::python::object obj) -> mitk::Image::Pointer
            {
                Image* imageData = boost::python::extract<Image*>(obj.ptr());

                boost::numpy::ndarray py_origin = imageData->getOrigin();
                boost::numpy::ndarray py_spacing = imageData->getSpacing();
                boost::numpy::ndarray py_data = imageData->getData();

                double*ds = NULL;

                mitk::Image::Pointer mitkImage = mitk::Image::New();
                mitk::Vector3D spacing;
                mitk::Point3D origin;

                std::string dtype = boost::python::extract<std::string>(boost::python::str(py_data.get_dtype()));

                unsigned int nr_components = boost::python::extract<unsigned int>(imageData->getNumberOfComponents());
                unsigned int nr_dimensions = py_data.get_nd();

                if (nr_components > 1)
                {
                    --nr_dimensions;
                }

                mitk::PixelType pixelType = mitk::MakePixelType<short, short, 1>();

                if(nr_components == 1)
                {
                    if( dtype.compare("float64") == 0   ) {
                        pixelType = mitk::MakePixelType<double, double, 1>();
                    } else if( dtype.compare("float32") == 0 ) {
                        pixelType = mitk::MakePixelType<float, float, 1>();
                    } else if( dtype.compare("int16") == 0) {
                        pixelType = mitk::MakePixelType<short, short, 1>();
                    } else if( dtype.compare("int8") == 0 ) {
                        pixelType = mitk::MakePixelType<char, char, 1>();
                    } else if( dtype.compare("int32") == 0 ) {
                        pixelType = mitk::MakePixelType<int, int, 1>();
                    } else if( dtype.compare("int64") == 0 ) {
                        pixelType = mitk::MakePixelType<long, long, 1>();
                    } else if( dtype.compare("uint8") == 0 ) {
                        pixelType = mitk::MakePixelType<unsigned char, unsigned char, 1>();
                    } else if( dtype.compare("uint32") == 0 ) {
                        pixelType = mitk::MakePixelType<unsigned int, unsigned int, 1>();
                    } else if( dtype.compare("uint64") == 0 ) {
                        pixelType = mitk::MakePixelType<unsigned long, unsigned long, 1>();
                    } else if( dtype.compare("uint16") == 0 ) {
                        pixelType = mitk::MakePixelType<unsigned short, unsigned short, 1>();
                    }
                }
                else if (nr_components == 3)
                {
                    if( dtype.compare("float64") == 0   ) {
                        pixelType = mitk::MakePixelType<double, double, 3>();
                    } else if( dtype.compare("float32") == 0 ) {
                        pixelType = mitk::MakePixelType<float, float, 3>();
                    } else if( dtype.compare("int16") == 0) {
                        pixelType = mitk::MakePixelType<short, short, 3>();
                    } else if( dtype.compare("int8") == 0 ) {
                        pixelType = mitk::MakePixelType<char, char, 3>();
                    } else if( dtype.compare("int32") == 0 ) {
                        pixelType = mitk::MakePixelType<int, int, 3>();
                    } else if( dtype.compare("int64") == 0 ) {
                        pixelType = mitk::MakePixelType<long, long, 3>();
                    } else if( dtype.compare("uint8") == 0 ) {
                        pixelType = mitk::MakePixelType<unsigned char, unsigned char, 3>();
                    } else if( dtype.compare("uint32") == 0 ) {
                        pixelType = mitk::MakePixelType<unsigned int, unsigned int, 3>();
                    } else if( dtype.compare("uint64") == 0 ) {
                        pixelType = mitk::MakePixelType<unsigned long, unsigned long, 3>();
                    } else if( dtype.compare("uint16") == 0 ) {
                        pixelType = mitk::MakePixelType<unsigned short, unsigned short, 3>();
                    }
                }
                else if (nr_components == 4)
                {
                    if( dtype.compare("float64") == 0   ) {
                        pixelType = mitk::MakePixelType<double, double, 4>();
                    } else if( dtype.compare("float32") == 0 ) {
                        pixelType = mitk::MakePixelType<float, float, 4>();
                    } else if( dtype.compare("int16") == 0) {
                        pixelType = mitk::MakePixelType<short, short, 4>();
                    } else if( dtype.compare("int8") == 0 ) {
                        pixelType = mitk::MakePixelType<char, char, 4>();
                    } else if( dtype.compare("int32") == 0 ) {
                        pixelType = mitk::MakePixelType<int, int, 4>();
                    } else if( dtype.compare("int64") == 0 ) {
                        pixelType = mitk::MakePixelType<long, long, 4>();
                    } else if( dtype.compare("uint8") == 0 ) {
                        pixelType = mitk::MakePixelType<unsigned char, unsigned char, 4>();
                    } else if( dtype.compare("uint32") == 0 ) {
                        pixelType = mitk::MakePixelType<unsigned int, unsigned int, 4>();
                    } else if( dtype.compare("uint64") == 0 ) {
                        pixelType = mitk::MakePixelType<unsigned long, unsigned long, 4>();
                    } else if( dtype.compare("uint16") == 0 ) {
                        pixelType = mitk::MakePixelType<unsigned short, unsigned short, 4>();
                    }
                }
                else
                {
                    throw "Unsupported";
                }

                unsigned int* dimensions = new unsigned int[nr_dimensions];

                for(int i=0; i < nr_dimensions; i++)
                {
                    dimensions[i] = py_data.get_shape()[nr_dimensions-i-1];
                }

                mitkImage->Initialize(pixelType, nr_dimensions, dimensions);
                mitkImage->SetChannel(py_data.get_data());
                
                ds = (double*)py_spacing.get_data();
                spacing[0] = ds[0];
                spacing[1] = ds[1];
                spacing[2] = ds[2];
                mitkImage->GetGeometry()->SetSpacing(spacing);
                
                ds = (double*)py_origin.get_data();
                origin[0] = ds[0];
                origin[1] = ds[1];
                origin[2] = ds[2];
                mitkImage->GetGeometry()->SetOrigin(origin);

                return mitkImage;
            }
        }
    }
}