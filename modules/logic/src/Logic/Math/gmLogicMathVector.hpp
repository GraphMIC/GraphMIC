#pragma once

#include "gmLogicMathBase.hpp"

#include "gmDataVector.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Math
        {
            class Vector : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto vector    = "vector";
                    static constexpr auto output    = "output";
                };
                
                static Register<Vector> Register;
                
                Vector() : Base("Vector")
                {
                    log_trace(Log::New);

                    auto param  = new Param::Vector(ID::vector, {"x", "y", "z", "w"});
                    auto output = new Slot::Output<Data::Vector>(ID::output);
                    output->addVector(new Data::Vector(0,0,0,0));

                    param->link(output);

                    this->add(param);
                    this->add(output);
                }
                
                auto run() -> void override
                {
                    log_trace(Log::Func);
                }
            };
        }
    }
}