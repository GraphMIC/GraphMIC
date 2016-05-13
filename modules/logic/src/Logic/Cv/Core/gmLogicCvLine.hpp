#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Line : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto linePoints = "line points";
                    static constexpr auto lineColor = "line color";
                    static constexpr auto thickness = "thickness";
                    static constexpr auto output = "output";
                };

                static Register<Line> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                Line() : Base("Line")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Pointset>(ID::linePoints, Data::Required));
                    this->add(new Param::Vector(ID::lineColor, {"R", "G", "B"}, 255, 0, 0));
                    this->add(new Param::Number(ID::thickness, 1));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Image>(ID::output);
                    auto linePoints = this->getInput<Data::Pointset>(ID::linePoints)->getPointset()->getPoints();
                    auto colorVector = this->getParam<Param::Vector>(ID::lineColor)->getValues();
                    auto thickness = this->getParam<Param::Number>(ID::thickness)->getValue();
                    auto lineColor = cv::Scalar(colorVector[0], colorVector[1], colorVector[2]);

                    for (auto it : this->inputIterator())
                    {
                        auto image = Image::ToCv(it.image());

                        for (int i = 0; i < linePoints.size() - 1; i+=2)
                        {
                            auto p1 = linePoints.at(i);
                            auto p2 = linePoints.at(i+1);

                            cv::line(image, cv::Point(p1->getX(), p1->getY()), cv::Point(p2->getX(), p2->getY()), lineColor, thickness);
                        }

                        output->addImage(Image::FromCv(image));
                    }
                }
            };
        }
    }
}
