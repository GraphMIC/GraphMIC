#pragma once

#include "gmLogicBase.hpp"
#include "gmSlotInput.hpp"
#include "gmSlotOutput.hpp"
#include "gmDataImage.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Generic
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