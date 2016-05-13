#pragma once

#include "gmLogicBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class Base : public Logic::Base
            {
            public:
                Base(const QString& name) : Logic::Base("itk", name)
                {
                    log_trace(Log::New, this);
                }
                
                ~Base()
                {
                    log_trace(Log::Del, this);
                }

                auto invokable() -> Data::Image*;

                auto run() -> void = 0;
            };
        }
    }
}
