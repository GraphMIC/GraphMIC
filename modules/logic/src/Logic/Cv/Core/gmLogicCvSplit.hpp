#pragma once

#include "gmLogicCvBase.hpp"

#include <vector>

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Split : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto output_r = "R";
                    static constexpr auto output_g = "G";
                    static constexpr auto output_b = "B";
                };

                static Register<Split> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                Split() : Base("Split")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Output<Data::Image>(ID::output_r, Access::MakeConstraints()));
                    this->add(new Slot::Output<Data::Image>(ID::output_g, Access::MakeConstraints()));
                    this->add(new Slot::Output<Data::Image>(ID::output_b, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output_r = this->getOutput<Data::Image>(ID::output_r);
                    auto output_g = this->getOutput<Data::Image>(ID::output_g);
                    auto output_b = this->getOutput<Data::Image>(ID::output_b);

                    for (auto it : this->inputIterator())
                    {
                        std::vector<cv::Mat> vec;

                        cv::split(Image::ToCv(it.image()), (std::vector<cv::Mat>&)vec);

                        if (vec.size() < 2)
                        {
                            output_r->addImage(Image::FromCv(vec.at(0)));
                        }
                        else if (vec.size() < 3)
                        {
                            output_r->addImage(Image::FromCv(vec.at(0)));
                            output_g->addImage(Image::FromCv(vec.at(1)));
                        }
                        else if (vec.size() < 4)
                        {
                            output_r->addImage(Image::FromCv(vec.at(0)));
                            output_g->addImage(Image::FromCv(vec.at(1)));
                            output_b->addImage(Image::FromCv(vec.at(2)));
                        }
                    }
                }
            };
        }
    }
}
