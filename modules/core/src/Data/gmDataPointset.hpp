#pragma once

#include "gmDataBase.hpp"
#include "gmCoreExport.hpp"

#include <QQmlListProperty>
#include <QObject>

namespace gm
{
    namespace Data
    {
        class Vector;
        
        class GM_CORE_EXPORT Pointset : public Base
        {
            Q_OBJECT
            Q_PROPERTY(QQmlListProperty<gm::Data::Vector> points READ getPointList NOTIFY pointsChanged);
            Q_PROPERTY(int size READ getSize NOTIFY sizeChanged);
        private:
            QList<Data::Vector*> m_points;
            int m_size;
        public:
            static Type DataType;
        private:
            auto setSize(int) -> void;
        public:
            Pointset();
            auto getSize() -> int;
            auto getPointList() -> QQmlListProperty<Data::Vector>;
            auto getPoints() -> QList<Data::Vector*>;
            auto getPoint(int) -> Data::Vector*;
            auto addPoint(Data::Vector*) -> void;
            auto addPoint(double x, double y, double z = 0, double w = 0) -> void;
            auto clear() -> void;
            ~Pointset();
        signals:
            void pointsChanged();
            void sizeChanged();
        };
    }
}
