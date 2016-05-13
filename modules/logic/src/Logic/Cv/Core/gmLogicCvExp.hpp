#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Exp : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto output = "output";
                };

                static Register<Exp> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<float, double>
                >;

                Exp() : Base("Exp")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Image>(ID::output);

                    for (auto it : this->inputIterator())
                    {
                        auto dest = cv::Mat();

                        cv::exp(Image::ToCv(it.image()), dest);

                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
