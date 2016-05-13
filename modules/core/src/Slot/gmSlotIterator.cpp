#include "gmSlotIterator.hpp"

#include "gmDataBase.hpp"

#include "gmSlotInputBase.hpp"
#include "gmSlotOutputBase.hpp"

namespace gm
{
    namespace Slot
    {
        Iterator::Iterator(QList<gm::Slot::InputBase*> inputs, unsigned int iteration) : m_inputs(inputs), m_iteration(iteration)
        {

        }

        auto Iterator::iteration() -> unsigned int
        {
            return this->m_iteration;
        }

        template <class TData>
        auto Iterator::input(int index) -> TData*
        {
            auto mockData = this->m_inputs.at(index)->getMockData();

            if (mockData.count() > 0)
            {
                auto data = mockData.at(m_iteration);

                if (data)
                {
                    return data->as<TData>();
                }
            }
            else
            {
                auto output = this->m_inputs.at(index)->getOutput();

                if (output)
                {
                    auto data = output->getData(m_iteration);

                    if (data)
                    {
                        return data->as<TData>();
                    }
                }
            }

            return nullptr;
        }

        auto Iterator::image(int index) -> Data::Image*
        {
            return input<Data::Image>(index);
        }

        auto Iterator::number(int index) -> Data::Number*
        {
            return input<Data::Number>(index);
        }

        auto Iterator::vector(int index) -> Data::Vector*
        {
            return input<Data::Vector>(index);
        }

        template auto Iterator::input<Data::Image>(int index) -> Data::Image*;
        template auto Iterator::input<Data::Number>(int index) -> Data::Number*;
        template auto Iterator::input<Data::Vector>(int index) -> Data::Vector*;
    }
}
