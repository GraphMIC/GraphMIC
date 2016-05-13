#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Compare : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input1 = "input 1";
                    static constexpr auto input2 = "input 2";
                    static constexpr auto comparison = "comparision";
                    static constexpr auto output = "output";
                };

                static Register<Compare> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                Compare() : Base("Compare")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input1, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::input2, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Option(ID::comparison, {
                        "input1 == input2",
                        "input1 >  input2",
                        "input1 >= input2",
                        "input1 <  input2",
                        "intpu1 <= input2",
                        "input1 != input2"}
                    ));

                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Image>(ID::output);
                    auto comparison = this->getParam<Param::Option>(ID::comparison)->getIndex();
                    auto compop = 0;

                    switch (comparison)
                    {
                        case 0: compop = cv::CMP_EQ; break;
                        case 1: compop = cv::CMP_GT; break;
                        case 2: compop = cv::CMP_GE; break;
                        case 3: compop = cv::CMP_LT; break;
                        case 4: compop = cv::CMP_LE; break;
                        case 5: compop = cv::CMP_NE; break;
                    }

                    for (auto it : this->inputIterator())
                    {
                        auto dest = cv::Mat();

                        cv::compare(Image::ToCv(it.image(0)), Image::ToCv(it.image(1)), dest, compop);

                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
