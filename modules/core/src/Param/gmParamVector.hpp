#pragma once

#include "gmParamBase.hpp"

#include <array>

namespace gm
{
    namespace Slot
    {
        template <class T> class Output;
    }

    namespace Data
    {
        class Vector;
    };

    namespace Param
    {
        class GM_CORE_EXPORT Vector : public Base
        {
            Q_OBJECT
            Q_PROPERTY(double x READ getX WRITE setX NOTIFY xChanged);
            Q_PROPERTY(double y READ getY WRITE setY NOTIFY yChanged);
            Q_PROPERTY(double z READ getZ WRITE setZ NOTIFY zChanged);
            Q_PROPERTY(double w READ getW WRITE setW NOTIFY wChanged);
            Q_PROPERTY(QStringList labels READ getLabels NOTIFY labelsChanged);
        private:
            Slot::Output<Data::Vector>* m_output;
            QStringList m_labels;
            std::array<double, 4> m_values;
        public:
            static Component::Type ComponentType;
            Vector(const QString&, QStringList);
            Vector(const QString&, QStringList, double);
            Vector(const QString&, QStringList, std::array<double, 4>);
            Vector(const QString&, QStringList, double, double, double, double=0);
            auto setX(double) -> void;
            auto getX() -> double;
            auto setY(double) -> void;
            auto getY() -> double;
            auto setZ(double) -> void;
            auto getZ() -> double;
            auto setW(double) -> void;
            auto getW() -> double;
            auto setLabels(QStringList) -> void;
            auto getLabels() -> QStringList;
            auto getValues() -> std::array<double, 4>;
            auto link(Slot::Output<Data::Vector>*) -> void;
        signals:
            void labelsChanged();
            void xChanged();
            void yChanged();
            void zChanged();
            void wChanged();
        };
    }
}