#include "gmSlotInput.hpp"
#include "gmSlotOutput.hpp"
#include "gmSlotConstraints.hpp"

#include "gmNodeObject.hpp"

namespace gm
{
    namespace Slot
    {
        template <class TData> Data::Type Input<TData>::DataType = TData::DataType;

        Input<Data::Image>::Input(const QString& name, Slot::Constraints* imageConstraints, Data::Connection connection) : InputBase(name, Data::Type::Image, connection, imageConstraints)
        {
            log_trace(Log::New, this);
        }

        Input<Data::Number>::Input(const QString& name, Data::Connection connection) : InputBase(name, Data::Type::Number, connection)
        {

        }

        Input<Data::Vector>::Input(const QString& name, Data::Connection connection) : InputBase(name, Data::Type::Vector, connection)
        {
            
        }

        Input<Data::Pointset>::Input(const QString& name, Data::Connection connection) : InputBase(name, Data::Type::Pointset, connection)
        {

        }

        auto Input<Data::Image>::getImage(size_t index) -> Data::Image*
        {
            Data::Image* imageData = nullptr;

            if (this->m_mockData.size() > 0)
            {
                auto data = m_mockData.at(index);

                if (data)
                {
                    imageData = data->as<Data::Image>();
                }
            }
            else if (auto output = this->getOutput())
            {
                auto data = output->getData(index);

                if (data)
                {
                    imageData = data->as<Data::Image>();
                }
            }

            return imageData;
        }

        auto Input<Data::Number>::getNumber(size_t index) -> Data::Number*
        {
            if (this->m_mockData.size() > 0)
            {
                auto data = m_mockData.at(index);

                if (data)
                {
                    return data->as<Data::Number>();
                }
            }
            else if (auto output = this->getOutput())
            {
                auto data = output->getData(index);

                if (data)
                {
                    return data->as<Data::Number>();
                }
            }

            return nullptr;
        }

        auto Input<Data::Vector>::getVector(size_t index) -> Data::Vector*
        {
            if (this->m_mockData.size() > 0)
            {
                auto data = m_mockData.at(index);

                if (data)
                {
                    return data->as<Data::Vector>();
                }
            }
            else if (auto output = this->getOutput())
            {
                auto data = output->getData(index);

                if (data)
                {
                    return data->as<Data::Vector>();
                }
            }

            return nullptr;
        }

        auto Input<Data::Pointset>::getPointset(size_t index) -> Data::Pointset*
        {
            if (this->m_mockData.size() > 0)
            {
                auto data = m_mockData.at(index);

                if (data)
                {
                    return data->as<Data::Pointset>();
                }
            }
            else if (auto output = this->getOutput())
            {
                auto data = output->getData(index);

                if (data)
                {
                    return data->as<Data::Pointset>();
                }
            }

            return nullptr;
        }

        template class Input<Data::Image>;
        template class Input<Data::Vector>;
        template class Input<Data::Number>;
        template class Input<Data::Pointset>;
    }
}