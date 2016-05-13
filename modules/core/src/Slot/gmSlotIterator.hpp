#pragma ocne

#include "gmCoreExport.hpp"

#include <QList>

namespace gm
{
    namespace Data
    {
        class Image;
        class Number;
        class Vector;
    }

    namespace Slot
    {
        class InputBase;

        class GM_CORE_EXPORT Iterator
        {
        private:
            QList<Slot::InputBase*> m_inputs;
            unsigned int m_iteration;
        public:
            Iterator() = delete;
            Iterator(QList<Slot::InputBase*>, unsigned int);
            auto iteration() -> unsigned int;
            auto image(int = 0) -> Data::Image*;
            auto number(int = 0) -> Data::Number*;
            auto vector(int = 0) -> Data::Vector*;
            template <class TData>
            auto input(int = 0) -> TData*;
        };
    }
}