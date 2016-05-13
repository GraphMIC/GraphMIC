#include "gmSlotType.hpp"

namespace gm
{
    namespace Slot
    {
        auto TypeFromIndex(int index) -> Type
        {
            if (index == 0)
            {
                return Type::Input;
            }

            return Type::Output;
        }
    }
}
