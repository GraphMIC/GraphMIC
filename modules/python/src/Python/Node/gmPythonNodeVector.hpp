#pragma once

#include "gmPythonNodeParam.hpp"

#include <array>

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class Vector : public Param
            {
                Q_OBJECT
                Q_PROPERTY(int dimension READ getDimension WRITE setDimension NOTIFY dimensionChanged);
                Q_PROPERTY(double x READ getX WRITE setX NOTIFY xChanged);
                Q_PROPERTY(double y READ getY WRITE setY NOTIFY yChanged);
                Q_PROPERTY(double z READ getZ WRITE setZ NOTIFY zChanged);
                Q_PROPERTY(double w READ getW WRITE setW NOTIFY wChanged);
                Q_PROPERTY(QString xLabel READ getXLabel WRITE setXLabel NOTIFY xLabelChanged);
                Q_PROPERTY(QString yLabel READ getYLabel WRITE setYLabel NOTIFY yLabelChanged);
                Q_PROPERTY(QString zLabel READ getZLabel WRITE setZLabel NOTIFY zLabelChanged);
                Q_PROPERTY(QString wLabel READ getWLabel WRITE setWLabel NOTIFY wLabelChanged);
            private:
                std::array<double, 4> m_values;
                QString m_xLabel;
                QString m_yLabel;
                QString m_zLabel;
                QString m_wLabel;
                int m_dimension;
            public:
                Vector(Object*);
                auto setX(double) -> void;
                auto getX() -> double;
                auto setY(double) -> void;
                auto getY() -> double;
                auto setZ(double) -> void;
                auto getZ() -> double;
                auto setW(double) -> void;
                auto getW() -> double;
                auto setDimension(int) -> void;
                auto getDimension() -> int;
                auto setXLabel(QString) -> void;
                auto getXLabel() -> QString;
                auto setYLabel(QString) -> void;
                auto getYLabel() -> QString;
                auto setZLabel(QString) -> void;
                auto getZLabel() -> QString;
                auto setWLabel(QString) -> void;
                auto getWLabel() -> QString;
                auto getValues() -> std::array<double, 4>;
                auto getLabels() -> QStringList;
            signals:
                void xChanged();
                void yChanged();
                void zChanged();
                void wChanged();
                void xLabelChanged();
                void yLabelChanged();
                void zLabelChanged();
                void wLabelChanged();
                void dimensionChanged();
            };
        }
    }
}