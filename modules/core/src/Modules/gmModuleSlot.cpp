#include "gmModuleSlot.hpp"

#include "gmSlotBase.hpp"
#include "gmSlotDataList.hpp"
#include "gmSlotInputList.hpp"
#include "gmSlotInputBase.hpp"
#include "gmSlotOutputList.hpp"
#include "gmSlotOutputBase.hpp"
#include "gmSlotConstraints.hpp"

namespace gm
{
    namespace Module
    {        
        auto Slot::Initialize() -> void
        {
            log_trace(Log::Func);

            registerType<gm::Slot::Constraints>();
            registerType<gm::Slot::Base>();
            registerType<gm::Slot::InputBase>();
            registerType<gm::Slot::OutputBase>();
            registerType<gm::Slot::InputList>();
            registerType<gm::Slot::OutputList>();
            registerType<gm::Slot::DataList>();
        }
    }
}