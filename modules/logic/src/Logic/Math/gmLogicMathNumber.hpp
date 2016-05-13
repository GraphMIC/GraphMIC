#pragma once

#include "gmLogicMathBase.hpp"

#include "gmDataVector.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Math
        {
            class Number : public Base
            {
            public:
                struct ID
                {
                    static constexpr auto number    = "number";
                    static constexpr auto output    = "output";
                };

                static Register<Number> Register;

                Number() : Base("Number")
                {
                    log_trace(Log::New);

                    auto param  = new Param::Number(ID::number);
                    auto output = new Slot::Output<Data::Number>(ID::output);

                    output->addNumber(new Data::Number(0));
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