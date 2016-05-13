#include "gmPreviewVectorViewer.hpp"
#include "gmPreviewController.hpp"
#include "gmSlotOutputBase.hpp"
#include "gmDataBase.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace Preview
    {
        VectorViewer::VectorViewer()
        {
            log_trace(Log::New, this);

            this->m_output      = nullptr;
            this->m_vector      = nullptr;
            this->m_stackIndex  = 0;
            this->m_stackSize   = 0;

            QObject::connect(Preview::Controller::instance, &Preview::Controller::stackIndexChanged, this, [this](){
                this->setStackIndex(Preview::Controller::instance->getStackIndex());
            });
        }

        auto VectorViewer::setStackIndex(int stackIndex) -> void
        {
            log_trace(Log::Set, stackIndex);

            if (this->m_stackIndex != stackIndex)
            {
                this->m_stackIndex = stackIndex;
                emit this->stackIndexChanged();

                this->updateData();
            }
        }

        auto VectorViewer::getStackIndex() -> int
        {
            return this->m_stackIndex;
        }

        auto VectorViewer::setStackSize(int stackSize) -> void
        {
            log_trace(Log::Set, stackSize);

            if (this->m_stackSize != stackSize)
            {
                this->m_stackSize = stackSize;
                emit this->stackSizeChanged();
            }
        }

        auto VectorViewer::getStackSize() -> int
        {
            return this->m_stackSize;
        }

        auto VectorViewer::updateData() -> void
        {
            log_trace(Log::Func);

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
                        this->setVector(data->as<Data::Vector>());
                    }
                }
            }
            else
            {
                this->setStackSize(0);
            }
        }

        auto VectorViewer::setOutput(Slot::OutputBase* output) -> void
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

        auto VectorViewer::getOutput() -> Slot::OutputBase*
        {
            return this->m_output;
        }

        auto VectorViewer::setVector(Data::Vector* vector) -> void
        {
            log_trace(Log::Set, vector);

            if (this->m_vector != vector)
            {
                this->m_vector = vector;
                emit this->vectorChanged();
            }
        }

        auto VectorViewer::getVector() -> Data::Vector*
        {
            return this->m_vector;
        }

        VectorViewer::~VectorViewer()
        {
            log_trace(Log::Del, this);
        }
    }
}