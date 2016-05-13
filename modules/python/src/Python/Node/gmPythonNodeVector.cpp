#include "gmPythonNodeVector.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            Vector::Vector(Object* node) : Param(gm::Component::Type::Vector, node), m_values{{0,0,0,0}}
            {
                this->setName("vector   param");

                this->m_xLabel = "x";
                this->m_yLabel = "y";
                this->m_zLabel = "z";
                this->m_wLabel = "w";

                this->m_dimension = 3;
            }

            auto Vector::setDimension(int dimension) -> void
            {
                if (this->m_dimension != dimension)
                {
                    this->m_dimension = dimension;
                    emit this->dimensionChanged();
                }
            }

            auto Vector::getDimension() -> int
            {
                return this->m_dimension;
            }
            
            auto Vector::setX(double value) -> void
            {
                this->m_values[0] = value;
                emit this->xChanged();
            }

            auto Vector::getX() -> double
            {
                return this->m_values[0];
            }

            auto Vector::setY(double value) -> void
            {
                this->m_values[1] = value;
                emit this->yChanged();
            }

            auto Vector::getY() -> double
            {
                return this->m_values[1];
            }

            auto Vector::setZ(double value) -> void
            {
                this->m_values[2] = value;
                emit this->zChanged();
            }

            auto Vector::getZ() -> double
            {
                return this->m_values[2];
            }

            auto Vector::setW(double value) -> void
            {
                this->m_values[3] = value;
                emit this->wChanged();
            }

            auto Vector::getW() -> double
            {
                return this->m_values[3];
            }

            auto Vector::setXLabel(QString xLabel) -> void
            {
                this->m_xLabel = xLabel;
                emit this->xLabelChanged();
            }

            auto Vector::getXLabel() -> QString
            {
                return this->m_xLabel;
            }

            auto Vector::setYLabel(QString yLabel) -> void
            {
                this->m_yLabel = yLabel;
                emit this->yLabelChanged();
            }

            auto Vector::getYLabel() -> QString
            {
                return this->m_yLabel;
            }

            auto Vector::setZLabel(QString zLabel) -> void
            {
                this->m_zLabel = zLabel;
                emit this->zLabelChanged();
            }

            auto Vector::getZLabel() -> QString
            {
                return this->m_zLabel;
            }

            auto Vector::setWLabel(QString wLabel) -> void
            {
                this->m_wLabel = wLabel;
                emit this->wLabelChanged();
            }

            auto Vector::getWLabel() -> QString
            {
                return this->m_wLabel;
            }

            auto Vector::getValues() -> std::array<double, 4>
            {
                return this->m_values;
            }

            auto Vector::getLabels() -> QStringList
            {
                QStringList labels;

                labels.append(this->m_xLabel);

                if (this->m_dimension > 1)
                {
                    labels.append(this->m_yLabel);
                }
                if (this->m_dimension > 2)
                {
                    labels.append(this->m_zLabel);
                }
                if (this->m_dimension > 3)
                {
                    labels.append(this->m_wLabel);
                }

                return labels;
            }
        }
    }
}
