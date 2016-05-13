#pragma once

#include "gmLogicCvBase.hpp"

#include <vector>

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class PreCornerDetect : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto kernelSize = "kernel size";
                    static constexpr auto output = "output";
                };

                static Register<PreCornerDetect> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                PreCornerDetect() : Base("PreCornerDetect")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::kernelSize, 3));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Image>(ID::output);
                    auto kernelSize = this->getParam<Param::Number>(ID::kernelSize)->getValue();

                    for (auto it : this->inputIterator())
                    {
                        auto dest = cv::Mat();

                        std::vector<cv::Vec4i> lines;

                        cv::preCornerDetect(Image::ToCv(it.image()), dest, kernelSize);

                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
