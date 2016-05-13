#include "gmLogicItkBase.hpp"
#include "gmSlotInputBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            auto Base::invokable() -> Data::Image*
            {
                log_trace(Log::Func);
                
                auto inputs = this->getInputs();
                
                if (inputs.empty())
                {
                    return nullptr;
                }
                
                for (auto input : inputs)
                {
                    if (input->getDataType() == Data::Type::Image)
                    {
                        auto mockData = input->getMockData();

                        if (mockData.count() > 0)
                        {
                            auto data = mockData.at(0);

                            if (data)
                            {
                                return data->as<Data::Image>();
                            }
                        }

                        auto output = input->getOutput();

                        if (output)
                        {
                            auto data = output->getData(0);

                            if (data)
                            {
                                return data->as<Data::Image>();
                            }
                        }
                    }
                }
                
                return nullptr;
            }
        }
    }
}