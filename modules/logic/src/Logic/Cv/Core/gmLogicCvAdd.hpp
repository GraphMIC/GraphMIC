#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Add : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input1 = "input 1";
                    static constexpr auto input2 = "input 2";
                    static constexpr auto mask = "mask";
                    static constexpr auto output = "output";
                };

                static Register<Add> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                Add() : Base("Add")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input1, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::input2, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::mask, Access::MakeConstraints(), Data::Optional));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Image>(ID::output);
                    auto mask = Image::ToCv(this->getInput<Data::Image>(ID::mask)->getImage());

                    for (auto it : this->inputIterator())
                    {
                        auto dest = cv::Mat();

                        cv::add(Image::ToCv(it.image(0)), Image::ToCv(it.image(1)), dest, mask);
                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
