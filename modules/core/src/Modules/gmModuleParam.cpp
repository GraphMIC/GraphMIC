#include "gmModuleParam.hpp"

#include "gmParamList.hpp"
#include "gmParamBase.hpp"
#include "gmParamBool.hpp"
#include "gmParamNumber.hpp"
#include "gmParamGroup.hpp"
#include "gmParamVector.hpp"
#include "gmParamGroupList.hpp"
#include "gmComponentBase.hpp"

namespace gm
{
    namespace Module
    {        
        auto Param::Initialize() -> void
        {
            log_trace(Log::Func);

            registerType<gm::Component::Base>();
            registerType<gm::Param::List>();
            registerType<gm::Param::GroupList>();
            registerType<gm::Param::Vector>();
            registerType<gm::Param::Group>();
            registerType<gm::Param::Base>();
            registerType<gm::Param::Bool>();
            registerType<gm::Param::Number>();
        }
    }
}