#pragma once

#include "gmLogicCvBase.hpp"

#include <vector>

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class CornerHarris : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto blockSize = "block size";
                    static constexpr auto kSize = "k size";
                    static constexpr auto k = "k";
                    static constexpr auto output = "output";
                };

                static Register<CornerHarris> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<unsigned char, unsigned short, char, short, float, double>,
                    Enable::Rgb<unsigned char, unsigned short, char, short>
                >;

                CornerHarris() : Base("CornerHarris")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Number(ID::blockSize, 3));
                    this->add(new Param::Number(ID::kSize, 3));
                    this->add(new Param::Number(ID::k, 0.04));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Image>(ID::output);
                    auto blockSize = this->getParam<Param::Number>(ID::blockSize)->getValue();
                    auto kSize = this->getParam<Param::Number>(ID::kSize)->getValue();
                    auto k = this->getParam<Param::Number>(ID::k)->getValue();

                    for (auto it : this->inputIterator())
                    {
                        auto dest = cv::Mat();

                        std::vector<cv::Vec4i> lines;

                        cv::cornerHarris(Image::ToCv(it.image()), dest, blockSize, kSize, k);

                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
