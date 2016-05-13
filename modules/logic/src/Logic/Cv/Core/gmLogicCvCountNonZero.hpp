#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class CountNonZero : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto output = "output";
                };

                static Register<CountNonZero> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                CountNonZero() : Base("CountNonZero")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Output<Data::Number>(ID::output));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Number>(ID::output);

                    for (auto it : this->inputIterator())
                    {
                        auto out = cv::countNonZero(Image::ToCv(it.image()));
                        output->addNumber(new Data::Number(out));
                    }
                }
            };
        }
    }
}
