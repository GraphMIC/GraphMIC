#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Transpose : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto output = "output";
                };

                static Register<Transpose> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                Transpose() : Base("Transpose")
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

                        cv::transpose(Image::ToCv(it.image()), dest);

                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
