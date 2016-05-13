#include "gmComponentType.hpp"

#include <QString>

namespace gm
{
    namespace Component
    {
        auto StringFromType(Type componentType) -> QString
        {
            switch(componentType)
            {
                case Type::Input: return "Slot::Input";
                case Type::Output: return "Slot::Output";
                case Type::Bool: return "Param::Bool";
                case Type::Number: return "Param::Number";
                case Type::String: return "Param::String";
                case Type::Option: return "Param::Option";
                case Type::Dir: return "Param::Dir";
                case Type::Files: return "Param::Files";
                case Type::Vector: return "Param::Vector";
            }
        }
    }
}