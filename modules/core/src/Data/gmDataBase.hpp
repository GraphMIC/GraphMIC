#pragma once

#include "gmCoreExport.hpp"
#include "gmDataType.hpp"

#include <QObject>

namespace gm
{
    namespace Data
    {
        class Image;
        class Vector;
        class Number;
        class Pointset;

        class GM_CORE_EXPORT Base : public QObject
        {
            Q_OBJECT
        private:
            Type m_dataType;
        public:
            Base() = delete;
            Base(Type dataType);
            virtual ~Base();
            template <class TData>
            auto as() -> TData*;
            auto getDataType() -> Type;
        };
    }
}