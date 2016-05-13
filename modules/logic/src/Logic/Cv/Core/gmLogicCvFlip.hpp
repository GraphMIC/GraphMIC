#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Flip : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto flip = "flip";
                    static constexpr auto output = "output";
                };

                static Register<Flip> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                Flip() : Base("Flip")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Option(ID::flip, {
                        "x",
                        "y",
                        "x/y"}
                    ));

                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Image>(ID::output);
                    auto flip = this->getParam<Param::Option>(ID::flip)->getIndex();
                    auto flipCode = -1;

                    if (flip == 0)
                    {
                        flipCode = 1;
                    }
                    else if (flip == 1)
                    {
                        flipCode = 0;
                    }

                    for (auto it : this->inputIterator())
                    {
                        auto dest = cv::Mat();

                        cv::flip(Image::ToCv(it.image()), dest, flipCode);

                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
