#include "gmPreviewPointsetViewer.hpp"
#include "gmPreviewController.hpp"
#include "gmSlotOutputBase.hpp"
#include "gmDataBase.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace Preview
    {
        PointsetViewer::PointsetViewer()
        {
            log_trace(Log::New, this);

            this->m_output      = nullptr;
            this->m_pointset    = nullptr;
            this->m_stackIndex  = 0;
            this->m_stackSize   = 0;

            QObject::connect(Preview::Controller::instance, &Preview::Controller::stackIndexChanged, this, [this](){
                this->setStackIndex(Preview::Controller::instance->getStackIndex());
            });
        }

        auto PointsetViewer::setStackIndex(int stackIndex) -> void
        {
            log_trace(Log::Set, stackIndex);

            if (this->m_stackIndex != stackIndex)
            {
                this->m_stackIndex = stackIndex;
                emit this->stackIndexChanged();

                this->updateData();
            }
        }

        auto PointsetViewer::getStackIndex() -> int
        {
            return this->m_stackIndex;
        }

        auto PointsetViewer::setStackSize(int stackSize) -> void
        {
            log_trace(Log::Set, stackSize);

            if (this->m_stackSize != stackSize)
            {
                this->m_stackSize = stackSize;
                emit this->stackSizeChanged();
            }
        }

        auto PointsetViewer::getStackSize() -> int
        {
            return this->m_stackSize;
        }

        auto PointsetViewer::updateData() -> void
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
                        this->setPointset(data->as<Data::Pointset>());
                    }
                }
            }
            else
            {
                this->setStackSize(0);
            }
        }

        auto PointsetViewer::setOutput(Slot::OutputBase* output) -> void
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

        auto PointsetViewer::getOutput() -> Slot::OutputBase*
        {
            return this->m_output;
        }

        auto PointsetViewer::setPointset(Data::Pointset* pointset) -> void
        {
            log_trace(Log::Set, pointset);

            if (this->m_pointset != pointset)
            {
                this->m_pointset = pointset;
                emit this->pointsetChanged();
            }
        }
        
        auto PointsetViewer::getPointset() -> Data::Pointset*
        {
            return this->m_pointset;
        }
        
        PointsetViewer::~PointsetViewer()
        {
            log_trace(Log::Del, this);
        }
    }
}