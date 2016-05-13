#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Mean : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto mask = "mask";
                    static constexpr auto output = "mean value";
                };

                static Register<Mean> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                Mean() : Base("Mean")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::mask, Access::MakeConstraints(), Data::Optional));
                    this->add(new Slot::Output<Data::Vector>(ID::output));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Vector>(ID::output);
                    auto mask = Image::ToCv(this->getInput<Data::Image>(ID::mask)->getImage());

                    for (auto it : this->inputIterator())
                    {
                        auto out = cv::mean(Image::ToCv(it.image()), mask);

                        output->addVector(new Data::Vector(out[0], out[1], out[2], out[3]));
                    }
                }
            };
        }
    }
}
