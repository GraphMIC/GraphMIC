#pragma once

#include <string>

#include "gmCoreExport.hpp"

namespace gm
{
    namespace IO
    {
        class GM_CORE_EXPORT Exceptions
        {
        private:
            Exceptions() = delete;
            ~Exceptions() = delete;
        public:
            static const std::string FileNotFound;
        };
    }
}