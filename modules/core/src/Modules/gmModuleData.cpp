#include "gmModuleData.hpp"
#include "gmDataVector.hpp"
#include "gmDataNumber.hpp"
#include "gmDataImage.hpp"
#include "gmDataPointset.hpp"

namespace gm
{
    namespace Module
    {        
        auto Data::Initialize() -> void
        {
            log_trace(Log::Func);

            registerType<gm::Data::Base>();
            registerType<gm::Data::Image>();
            registerType<gm::Data::Number>();
            registerType<gm::Data::Vector>();
            registerType<gm::Data::Pointset>();
        }
    }
}