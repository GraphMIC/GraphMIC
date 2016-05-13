#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Determinant : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto output = "determinant";
                };

                static Register<Determinant> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<float, double>
                >;

                Determinant() : Base("Determinant")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Output<Data::Number>(ID::output));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Number>(ID::output);

                    for (auto it : this->inputIterator())
                    {
                        auto out = cv::determinant(Image::ToCv(it.image()));
                        output->addNumber(new Data::Number(out));
                    }
                }
            };
        }
    }
}
