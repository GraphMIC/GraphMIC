#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class AddWeighted : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input1 = "input 1";
                    static constexpr auto input2 = "input 2";
                    static constexpr auto alpha = "alpha";
                    static constexpr auto beta = "beta";
                    static constexpr auto gamma = "gamma";
                    static constexpr auto output = "output";
                };

                static Register<AddWeighted> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                AddWeighted() : Base("AddWeighted")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input1, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::input2, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::alpha, 0.5));
                    this->add(new Param::Number(ID::beta, 0.5));
                    this->add(new Param::Number(ID::gamma, 0));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Image>(ID::output);
                    
                    auto alpha  = this->getParam<Param::Number>(ID::alpha)->getValue();
                    auto beta   = this->getParam<Param::Number>(ID::beta)->getValue();
                    auto gamma  = this->getParam<Param::Number>(ID::gamma)->getValue();

                    for (auto it : this->inputIterator())
                    {
                        auto dest = cv::Mat();

                        cv::addWeighted(Image::ToCv(it.image(0)), alpha, Image::ToCv(it.image(1)), beta, gamma, dest);

                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
