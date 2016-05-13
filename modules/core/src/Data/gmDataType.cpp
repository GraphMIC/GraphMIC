#include "gmDataType.hpp"

#include <QString>

namespace gm
{
    namespace Data
    {
        auto TypeFromIndex(int index) -> Type
        {
            if (index == 0)
            {
                return Type::Image;
            }
            else if (index == 1)
            {
                return Type::Number;
            }
            else if (index == 2)
            {
                return Type::Vector;
            }
            else if (index == 3)
            {
                return Type::Pointset;
            }

            return Type::Image;
        }

        auto TypeToIndex(Type type) -> int
        {
            switch (type)
            {
                case Type::Image:
                    return 0;
                    break;
                case Type::Number:
                    return 1;
                    break;
                case Type::Vector:
                    return 2;
                    break;
                case Type::Pointset:
                    return 3;
                    break;
            }
        }

        auto TypeToString(Type type) -> QString
        {
            switch (type)
            {
                case Type::Image:
                    return "image";
                    break;
                case Type::Number:
                    return "number";
                    break;
                case Type::Vector:
                    return "vector";
                    break;
                case Type::Pointset:
                    return "pointset";
                    break;
            }
        }
    }
}