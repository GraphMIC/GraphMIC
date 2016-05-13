#include "gmDataPointset.hpp"
#include "gmDataVector.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace Data
    {
        Type Pointset::DataType = Type::Pointset;

        Pointset::Pointset() : Base(DataType)
        {
            log_trace(Log::New, this);

            this->m_size = 0;
        }

        auto Pointset::setSize(int size) -> void
        {
            if (this->m_size != size)
            {
                this->m_size = size;
                emit this->sizeChanged();
            }
        }

        auto Pointset::getSize() -> int
        {
            return this->m_size;
        }

        auto Pointset::addPoint(Data::Vector* point) -> void
        {
            if (point)
            {
                this->m_points.append(point);
                this->setSize(this->m_points.size());

                emit this->pointsChanged();
            }
        }

        auto Pointset::addPoint(double x, double y, double z, double w) -> void
        {
            this->addPoint(new Vector(x,y,z,w));
        }

        auto Pointset::getPoint(int index) -> Data::Vector*
        {
            return this->m_points.at(index);
        }

        auto Pointset::getPoints() -> QList<Data::Vector*>
        {
            return this->m_points;
        }

        auto Pointset::getPointList() -> QQmlListProperty<Data::Vector>
        {
            return QQmlListProperty<Data::Vector>(this, this->m_points);
        }

        auto Pointset::clear() -> void
        {
            this->setSize(0);

            for (auto point : this->m_points)
            {
                delete point;
            }

            this->m_points.clear();
        }

        Pointset::~Pointset()
        {
            log_trace(Log::Del, this);

            this->clear();
        }
    }
}
