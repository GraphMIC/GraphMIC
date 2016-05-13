#include "gmPreviewNumberViewer.hpp"
#include "gmPreviewController.hpp"
#include "gmSlotOutputBase.hpp"
#include "gmDataBase.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace Preview
    {
        NumberViewer::NumberViewer()
        {
            log_trace(Log::New, this);

            this->m_output      = nullptr;
            this->m_number      = nullptr;
            this->m_stackIndex  = 0;
            this->m_stackSize   = 0;

            QObject::connect(Preview::Controller::instance, &Preview::Controller::stackIndexChanged, this, [this](){
                this->setStackIndex(Preview::Controller::instance->getStackIndex());
            });
        }

        auto NumberViewer::setStackIndex(int stackIndex) -> void
        {
            log_trace(Log::Set, stackIndex);

            if (this->m_stackIndex != stackIndex)
            {
                this->m_stackIndex = stackIndex;
                emit this->stackIndexChanged();

                this->updateData();
            }
        }

        auto NumberViewer::getStackIndex() -> int
        {
            return this->m_stackIndex;
        }

        auto NumberViewer::setStackSize(int stackSize) -> void
        {
            log_trace(Log::Set, stackSize);

            if (this->m_stackSize != stackSize)
            {
                this->m_stackSize = stackSize;
                emit this->stackSizeChanged();
            }
        }

        auto NumberViewer::getStackSize() -> int
        {
            return this->m_stackSize;
        }

        auto NumberViewer::updateData() -> void
        {
            if (this->m_output)
            {
                this->setStackSize(this->m_output->getDataCount());

                if (this->m_stackIndex >= this->m_output->getDataCount() && this->m_output->getDataCount() > 0)
                {
                    setStackIndex(0);
                }
                else
                {
                    auto data = this->m_output->getData(this->m_stackIndex);

                    if (data)
                    {
                        this->setNumber(data->as<Data::Number>());
                    }
                }
            }
            else
            {
                this->setStackSize(0);
            }
        }

        auto NumberViewer::setOutput(Slot::OutputBase* output) -> void
        {
            log_trace(Log::Set, output);

            if (this->m_output == output)
            {
                return;
            }

            this->m_output = output;
            emit this->outputChanged();

            if (output)
            {
                QObject::connect(output, &Slot::OutputBase::dataChanged, this, [this](){
                    this->updateData();
                });
            }

            this->updateData();
        }

        auto NumberViewer::getOutput() -> Slot::OutputBase*
        {
            return this->m_output;
        }

        auto NumberViewer::setNumber(Data::Number* number) -> void
        {
            log_trace(Log::Set, number);

            if (this->m_number != number)
            {
                this->m_number = number;
                emit this->numberChanged();
            }
        }

        auto NumberViewer::getNumber() -> Data::Number*
        {
            return this->m_number;
        }

        NumberViewer::~NumberViewer()
        {
            log_trace(Log::Del, this);
        }
    }
}