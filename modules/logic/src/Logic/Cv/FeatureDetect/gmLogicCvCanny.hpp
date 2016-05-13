#pragma once

#include "gmLogicCvBase.hpp"

#include <vector>

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Canny : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto threshold1 = "threshold 1";
                    static constexpr auto threshold2 = "threshold 2";
                    static constexpr auto apertureSize = "aperture size";
                    static constexpr auto l2Gradient = "L2 gradient";
                    static constexpr auto output = "output";
                };

                static Register<Canny> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char>,
                    Enable::Rgb<unsigned char>
                >;

                Canny() : Base("Canny")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::threshold1, 100));
                    this->add(new Param::Number(ID::threshold2, 110));
                    this->add(new Param::Number(ID::apertureSize, 3));
                    this->add(new Param::Bool(ID::l2Gradient));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Image>(ID::output);
                    auto threshold1 = this->getParam<Param::Number>(ID::threshold1)->getValue();
                    auto threshold2 = this->getParam<Param::Number>(ID::threshold2)->getValue();
                    auto apertureSize = this->getParam<Param::Number>(ID::apertureSize)->getValue();
                    auto l2Gradient = this->getParam<Param::Bool>(ID::l2Gradient)->getValue();

                    for (auto it : this->inputIterator())
                    {
                        auto dest = cv::Mat();

                        std::vector<cv::Vec4i> lines;

                        cv::Canny(Image::ToCv(it.image()), dest, threshold1, threshold2, apertureSize, l2Gradient);

                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
