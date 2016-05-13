#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Sort : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto flag1 = "direction";
                    static constexpr auto flag2 = "order";
                    static constexpr auto output = "output";
                };

                static Register<Sort> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                Sort() : Base("Sort")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Option(ID::flag1, {"rows", "columns"}));
                    this->add(new Param::Option(ID::flag2, {"ascending", "descending"}));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Image>(ID::output);
                    auto flagDirection = this->getParam<Param::Option>(ID::flag1)->getIndex() == 0 ? CV_SORT_EVERY_ROW : CV_SORT_EVERY_COLUMN;
                    auto flagOrder = this->getParam<Param::Option>(ID::flag2)->getIndex() == 0? CV_SORT_ASCENDING : CV_SORT_DESCENDING;

                    for (auto it : this->inputIterator())
                    {
                        auto dest = cv::Mat();

                        cv::sort(Image::ToCv(it.image()), dest, flagDirection | flagOrder);

                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
