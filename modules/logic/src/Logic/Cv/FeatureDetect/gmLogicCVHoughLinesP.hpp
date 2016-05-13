#pragma once

#include "gmLogicCvBase.hpp"

#include <vector>

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class HoughLinesP : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto rho = "rho";
                    static constexpr auto theta = "theta";
                    static constexpr auto threshold = "threshold";
                    static constexpr auto minLineLength = "minLineLength";
                    static constexpr auto maxLineGap = "maxLineGap";
                    static constexpr auto linePoints = "line points";
                };

                static Register<HoughLinesP> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                HoughLinesP() : Base("HoughLinesP")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::rho, 1));
                    this->add(new Param::Number(ID::theta, 0.02));
                    this->add(new Param::Number(ID::threshold, 80));
                    this->add(new Param::Number(ID::minLineLength, 30));
                    this->add(new Param::Number(ID::maxLineGap, 10));
                    this->add(new Slot::Output<Data::Pointset>(ID::linePoints));
                }

                auto run() -> void override
                {
                    auto linePoints   = this->getOutput<Data::Pointset>(ID::linePoints);
                    auto rho = this->getParam<Param::Number>(ID::rho)->getValue();
                    auto theta = this->getParam<Param::Number>(ID::theta)->getValue();
                    auto threshold = this->getParam<Param::Number>(ID::threshold)->getValue();
                    auto minLineLength = this->getParam<Param::Number>(ID::minLineLength)->getValue();
                    auto maxLineGap = this->getParam<Param::Number>(ID::maxLineGap)->getValue();

                    for (auto it : this->inputIterator())
                    {
                        cv::Mat src = Image::ToCv(it.image());

                        std::vector<cv::Vec2f> lines;
                        cv::HoughLinesP(src, lines, rho, theta, threshold, minLineLength, maxLineGap);

                        if (lines.size() > 0)
                        {
                            auto pointset = new Data::Pointset();

                            for( size_t i = 0; i < lines.size(); i++ )
                            {
                                auto pt1 = cv::Point(lines[i][0], lines[i][1]);
                                auto pt2 = cv::Point(lines[i][2], lines[i][3]);

                                pointset->addPoint(pt1.x, pt1.y);
                                pointset->addPoint(pt2.x, pt2.y);
                            }
                            
                            linePoints->addPointset(pointset);
                        }
                    }
                }
            };
        }
    }
}
