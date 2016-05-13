#pragma once

#include "gmLogicBase.hpp"
#include "gmLogicEnable.hpp"

#include "gmImageConvert.hpp"

#include "gmSlotInput.hpp"
#include "gmSlotOutput.hpp"

#include "gmDataImage.hpp"
#include "gmDataVector.hpp"
#include "gmDataNumber.hpp"

#include <opencv/cv.h>

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            class Base : public Logic::Base
            {
            private:
            public:
                Base(const QString&);
                ~Base();
            };
        }
    }
}