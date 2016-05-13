#include "gmParamVector.hpp"
#include "gmSlotOutput.hpp"
#include "gmDataVector.hpp"

#include <QJsonObject>

namespace gm
{
    namespace Param
    {
        Component::Type Vector::ComponentType = Component::Type::Vector;
        
        Vector::Vector(const QString& name, QStringList labels, double x, double y, double z, double w) : Base(ComponentType, name), m_labels(labels), m_values{ {x,y,z,w} }
        {
            this->m_output = nullptr;

            log_trace(Log::New, this);
        }
        
        Vector::Vector(const QString& name, QStringList labels, double v) : Vector(name, labels, v, v, v, v)
        {
        }

        Vector::Vector(const QString& name, QStringList labels, std::array<double, 4> values) : Vector(name, labels, values[0], values[1], values[2], values[3])
        {
        }
        
        Vector::Vector(const QString& name, QStringList labels) : Vector(name, labels, 0)
        {
        }

        auto Vector::link(Slot::Output<Data::Vector>* output) -> void
        {
            this->m_output = output;
        }

        auto Vector::setX(double x) -> void
        {
            if (this->m_values[0] != x)
            {
                this->m_values[0] = x;
                emit this->xChanged();
                this->setModified(true);

                if (this->m_output)
                {
                    this->m_output->getVector()->setX(x);
                }
            }
        }
        
        auto Vector::getX() -> double
        {
            return this->m_values[0];
        }
        
        auto Vector::setY(double y) -> void
        {
            if (this->m_values[1] != y)
            {
                this->m_values[1] = y;
                emit this->yChanged();
                this->setModified(true);

                if (this->m_output)
                {
                    this->m_output->getVector()->setY(y);
                }
            }
        }
        
        auto Vector::getY() -> double
        {
            return this->m_values[1];
        }
        
        auto Vector::setZ(double z) -> void
        {
            if (this->m_values[2] != z)
            {
                this->m_values[2] = z;
                emit this->zChanged();
                this->setModified(true);

                if (this->m_output)
                {
                    this->m_output->getVector()->setZ(z);
                }
            }
        }
        
        auto Vector::getZ() -> double
        {
            return this->m_values[2];
        }
        
        auto Vector::setW(double w) -> void
        {
            if (this->m_values[3] != w)
            {
                this->m_values[3] = w;
                emit this->wChanged();
                this->setModified(true);

                if (this->m_output)
                {
                    this->m_output->getVector()->setW(w);
                }
            }
        }
        
        auto Vector::getW() -> double
        {
            return this->m_values[3];
        }
        
        auto Vector::getValues() -> std::array<double, 4>
        {
            return this->m_values;
        }
        
        auto Vector::setLabels(QStringList labels) -> void
        {
            this->m_labels = labels;
            emit this->labelsChanged();
        }
        
        auto Vector::getLabels() -> QStringList
        {
            return this->m_labels;
        }
    }
}