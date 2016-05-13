#pragma once

#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Invert : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto input = "input";
                    static constexpr auto inversionMethod = "inversion method";
                    static constexpr auto output = "output";
                };

                static Register<Invert> Register;

                using Access = Enable::ImageTypes <
                    Enable::Dimension<2>,
                    Enable::Scalar<float, double>
                >;

                Invert() : Base("Invert")
                {
                    this->add(new Slot::Input<Data::Image>(ID::input, Access::MakeConstraints(), Data::Required));
                    this->add(new Param::Option(ID::inversionMethod, {
                        "gaussian elimination",
                        "singular value decomposition method",
                        "cholesky decomposition"}
                    ));

                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }

                auto run() -> void override
                {
                    auto output = this->getOutput<Data::Image>(ID::output);
                    auto inversionMethod = this->getParam<Param::Option>(ID::inversionMethod)->getIndex();
                    auto methodFlag = 0;

                    if (inversionMethod == 0)
                    {
                        methodFlag = cv::DECOMP_LU;
                    }
                    else if (inversionMethod == 1)
                    {
                        methodFlag = cv::DECOMP_SVD;
                    }
                    else
                    {
                        methodFlag = cv::DECOMP_CHOLESKY;
                    }

                    for (auto it : this->inputIterator())
                    {
                        auto dest = cv::Mat();

                        cv::invert(Image::ToCv(it.image()), dest, methodFlag);

                        output->addImage(Image::FromCv(dest));
                    }
                }
            };
        }
    }
}
