#include "gmModuleUtil.hpp"

#include "gmUtilPathValidator.hpp"
#include "gmUtilRegexValidator.hpp"

namespace gm
{
    namespace Module
    {       
        auto Util::Initialize() -> void
        {
            log_trace(Log::Func);
            
            registerType<gm::Util::PathValidator>("Util", "PathValidator");
            registerType<gm::Util::RegexValidator>("Util", "RegexValidator");
        }
    }
}
