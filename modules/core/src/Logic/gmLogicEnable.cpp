#include "gmLogicEnable.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Enable
        {
            namespace Bitset
            {
                template<> const std::bitset<4> ForDimension<1>::bitset ("0001");
                template<> const std::bitset<4> ForDimension<2>::bitset ("0010");
                template<> const std::bitset<4> ForDimension<3>::bitset ("0100");
                template<> const std::bitset<4> ForDimension<4>::bitset ("1000");

                template<> const std::bitset<8> ForComponent<unsigned char>::bitset     ("00000001");
                template<> const std::bitset<8> ForComponent<unsigned short>::bitset    ("00000010");
                template<> const std::bitset<8> ForComponent<unsigned int>::bitset      ("00000100");
                template<> const std::bitset<8> ForComponent<char>::bitset              ("00001000");
                template<> const std::bitset<8> ForComponent<short>::bitset             ("00010000");
                template<> const std::bitset<8> ForComponent<int>::bitset               ("00100000");
                template<> const std::bitset<8> ForComponent<float>::bitset             ("01000000");
                template<> const std::bitset<8> ForComponent<double>::bitset            ("10000000");
            }
        }
    }
}
