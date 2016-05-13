#pragma once

#include "gmLogicGenericBase.hpp"
#include "gmIOPath.hpp"
#include "gmSlotConstraints.hpp"
#include "gmLogicEnable.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Generic
        {
            class ImageWriter : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input     = "input";
                    static constexpr auto imageName = "image name";
                    static constexpr auto directory = "directory";
                };
                
                static Register<ImageWriter> Register;
                
                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char>,
                    Enable::Rgb<unsigned char, unsigned short, unsigned int, char, short, int, float, double>,
                    Enable::Rgba<unsigned char, unsigned short, unsigned int, char, short, int, float, double>
                >;

                ImageWriter() : Base("ImageWriter")
                {
                    log_trace(Log::New, this);
                    
                    this->setRunnable(true);
                    this->setUseTimer(true);
                    
                    this->add(new Param::String(ID::imageName, "image.png", "\\w+\\.\\w"));
                    this->add(new Param::Dir(ID::directory, "Save..."));
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                }
                
                auto run() -> void override
                {
                    log_trace(Log::Func);

                    auto text   = this->getParam<Param::String>(ID::imageName)->getValue();
                    auto dir    = this->getParam<Param::Dir>(ID::directory)->getDir();
                    auto input  = this->getInput<Data::Image>(ID::input);
                    auto output = input->getOutput();


                    auto suffix = text.section('.', -1, -1);
                    auto name = text.section('.', -2, -2);

                    if (suffix.isEmpty())
                    {
                        throw new std::runtime_error("no file suffix found.");
                    }

                    if (output && output->getDataCount() > 1)
                    {
                        for (auto it : this->inputIterator())
                        {
                            it.image()->saveToDir(dir + "/" + name + "_" + QString::number(it.iteration()) + "." + suffix);
                        }
                    }
                    else
                    {
                        for (auto it : this->inputIterator())
                        {
                            it.image()->saveToDir(dir + "/" + name + "." + suffix);
                        }
                    }
                }
            };
        }
    }
}