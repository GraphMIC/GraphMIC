#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class ConvertScaleAbs : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto alpha = "alpha";
                    static constexpr auto beta = "beta";
                    static constexpr auto output = "output";
                };

                static Register<ConvertScaleAbs> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                ConvertScaleAbs() : Base("ConvertScaleAbs")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::alpha, 1));
                    this->add(new Param::Number(ID::beta, 0));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Image>(ID::output);
                    auto alpha  = this->getParam<Param::Number>(ID::alpha)->getValue();
                    auto beta   = this->getParam<Param::Number>(ID::beta)->getValue();

                    for (auto it : this->inputIterator())
                    {
                        auto dest = cv::Mat();

                        cv::convertScaleAbs(Image::ToCv(it.image()), dest, alpha, beta);

                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
