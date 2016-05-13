#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Sqrt : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto output = "output";
                };

                static Register<Sqrt> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                Sqrt() : Base("Sqrt")
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

                        cv::sqrt(Image::ToCv(it.image()), dest);

                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
