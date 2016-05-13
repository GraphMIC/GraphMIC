#pragma once

#include "gmDataBase.hpp"
#include "gmCoreExport.hpp"

#include <array>
#include <QObject>

namespace gm
{
    namespace Data
    {
        class GM_CORE_EXPORT Vector : public Base
        {
            Q_OBJECT
            Q_PROPERTY(bool isVector READ getIsVector CONSTANT);
            Q_PROPERTY(double x READ getX NOTIFY xChanged);
            Q_PROPERTY(double y READ getY NOTIFY yChanged);
            Q_PROPERTY(double z READ getZ NOTIFY zChanged);
            Q_PROPERTY(double w READ getW NOTIFY wChanged);
        private:
            std::array<double, 4> m_values;
        public:
            static Type DataType;
        private:
            auto getIsVector() -> bool;
        public:
            Vector(double x, double y, double z, double w);
            auto setX(double) -> void;
            auto getX() -> double;
            auto setY(double) -> void;
            auto getY() -> double;
            auto setZ(double) -> void;
            auto getZ() -> double;
            auto setW(double) -> void;
            auto getW() -> double;
            auto getValues() -> std::array<double, 4>;
            ~Vector();
        signals:
            void xChanged();
            void yChanged();
            void zChanged();
            void wChanged();
        };
    }
}
