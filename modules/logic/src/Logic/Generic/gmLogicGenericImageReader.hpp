#pragma once

#include "gmLogicGenericBase.hpp"
#include "gmLogicEnable.hpp"
#include "gmNodeObject.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Generic
        {
            class ImageReader : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto files      = "files";
                    static constexpr auto output     = "output";
                };
                
                static Register<ImageReader> Register;

                using Access = Enable::ImageTypes <
                Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                ImageReader() : Base("ImageReader")
                {
                    log_trace(Log::New, this);
                    
                    this->setIsDataSource(true);
                    this->setUseTimer(true);
                    this->setThreaded(true);
                    
                    this->add(new Param::Files(ID::files, "Load...", "Image files (*.bmp *.png *.jpeg *.jpg *.tif *.tiff *.dcm *.Image *.nii *.hdr *.mhd *.nrrd *.vtk)"));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                auto run() -> void override
                {
                    log_trace(Log::Func);
                    
                    auto urls = this->getParam<Param::Files>("files")->getFilePaths();
                    
                    if (urls.empty())
                    {
                        throw new std::runtime_error("No load path specified.");
                    }
                    
                    auto stack  = this->getOutput<Data::Image>(ID::output);
                    
                    for (auto url : urls)
                    {
                        stack->addImage(Data::Image::FromFile(url));
                    }
                }
                
                ~ImageReader()
                {
                    log_trace(Log::Del, this);
                }
            };
        }
    }
}