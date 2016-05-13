#include "gmDataVector.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace Data
    {
        Type Vector::DataType = Type::Vector;

        Vector::Vector(double x, double y, double z, double w) : Base(DataType)
        {
            this->m_values = {{x,y,z,w}};
        }

        auto Vector::getIsVector() -> bool
        {
            return true;
        }

        auto Vector::setX(double x) -> void
        {
            this->m_values[0] = x;
            emit this->xChanged();
        }

        auto Vector::getX() -> double
        {
            return this->m_values[0];
        }

        auto Vector::setY(double y) -> void
        {
            this->m_values[1] = y;
            emit this->yChanged();
        }

        auto Vector::getY() -> double
        {
            return this->m_values[1];
        }

        auto Vector::setZ(double z) -> void
        {
            this->m_values[2] = z;
            emit this->zChanged();
        }

        auto Vector::getZ() -> double
        {
            return this->m_values[2];
        }

        auto Vector::setW(double w) -> void
        {
            this->m_values[3] = w;
            emit this->wChanged();
        }

        auto Vector::getW() -> double
        {
            return this->m_values[3];
        }

        auto Vector::getValues() -> std::array<double, 4>
        {
            return this->m_values;
        }

        Vector::~Vector()
        {
        }
    }
}

