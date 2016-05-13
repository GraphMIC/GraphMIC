#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Sum : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto output = "sum";
                };

                static Register<Sum> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                Sum() : Base("Sum")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Output<Data::Vector>(ID::output));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Vector>(ID::output);

                    for (auto it : this->inputIterator())
                    {
                        auto out = cv::sum(Image::ToCv(it.image()));
                        output->addVector(new Data::Vector(out[0], out[1], out[2], out[3]));
                    }
                }
            };
        }
    }
}
