#pragma once

#include "gmLogicBase.hpp"
#include "gmSlotInput.hpp"
#include "gmSlotOutput.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Math
        {
            class Base : public Logic::Base
            {
            private:
            public:
                Base(const QString&);
                virtual ~Base();
            };
        }
    }
}