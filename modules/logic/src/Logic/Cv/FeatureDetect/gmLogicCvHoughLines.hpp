#pragma once

#include "gmLogicCvBase.hpp"

#include <vector>

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class HoughLines : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto rho = "rho";
                    static constexpr auto theta = "theta";
                    static constexpr auto threshold = "threshold";
                    static constexpr auto srn = "srn";
                    static constexpr auto stn = "stn";
                    static constexpr auto linePoints = "line points";
                };

                static Register<HoughLines> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                HoughLines() : Base("HoughLines")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::rho, 1));
                    this->add(new Param::Number(ID::theta, 0.02));
                    this->add(new Param::Number(ID::threshold, 50));
                    this->add(new Param::Number(ID::srn));
                    this->add(new Param::Number(ID::stn));
                    this->add(new Slot::Output<Data::Pointset>(ID::linePoints));
                }

                auto run() -> void override
                {
                    auto linePoints   = this->getOutput<Data::Pointset>(ID::linePoints);
                    auto rho = this->getParam<Param::Number>(ID::rho)->getValue();
                    auto theta = this->getParam<Param::Number>(ID::theta)->getValue();
                    auto threshold = this->getParam<Param::Number>(ID::threshold)->getValue();
                    auto srn = this->getParam<Param::Number>(ID::srn)->getValue();
                    auto stn = this->getParam<Param::Number>(ID::stn)->getValue();

                    for (auto it : this->inputIterator())
                    {
                        cv::Mat src = Image::ToCv(it.image());

                        std::vector<cv::Vec2f> lines;
                        cv::HoughLines(src, lines, rho, theta, threshold, srn, stn);

                        if (lines.size() > 0)
                        {
                            auto pointset = new Data::Pointset();

                            for( size_t i = 0; i < lines.size(); i++ )
                            {
                                cv::Point pt1, pt2;

                                float rho = lines[i][0], theta = lines[i][1];
                                double a = cos(theta), b = sin(theta);
                                double x0 = a*rho, y0 = b*rho;

                                pt1.x = cvRound(x0 + 1000*(-b));
                                pt1.y = cvRound(y0 + 1000*(a));
                                pt2.x = cvRound(x0 - 1000*(-b));
                                pt2.y = cvRound(y0 - 1000*(a));

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
