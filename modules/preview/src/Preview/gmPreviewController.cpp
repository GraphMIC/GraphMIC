#include "gmPreviewController.hpp"

#include "gmNodeObject.hpp"
#include "gmSlotOutputBase.hpp"
#include "gmSlotOutputList.hpp"
#include "gmDataImage.hpp"
#include "gmDataImage.hpp"
#include "gmLogicbase.hpp"

namespace gm
{
    namespace Preview
    {
        Controller* Controller::instance = nullptr;
        
        Controller::Controller() : m_empty(true)
        {
            log_trace(Log::New, this);
            
            if (instance)
            {
                throw "instance already existing";
            }

            this->m_pointsetOutputs = new Slot::OutputList();
            this->m_numberOutputs   = new Slot::OutputList();
            this->m_vectorOutputs   = new Slot::OutputList();
            this->m_imageOutputs    = new Slot::OutputList();

            this->m_node = nullptr;
            this->m_stackSize = 0;
            this->m_stackIndex = 0;
            
            instance = this;
        }
        
        auto Controller::Create() -> Controller*
        {
            return new Controller();
        }
        
        auto Controller::setEmpty(bool empty) -> void
        {
            log_trace(Log::Set, empty);
            
            if (this->m_empty != empty)
            {
                this->m_empty = empty;
                emit this->emptyChanged();
            }
        }
        
        auto Controller::getEmpty() -> bool
        {
            return this->m_empty;
        }

        auto Controller::getImageOutputs() -> Slot::OutputList*
        {
            return this->m_imageOutputs;
        }

        auto Controller::getNumberOutputs() -> Slot::OutputList*
        {
            return this->m_numberOutputs;
        }

        auto Controller::getVectorOutputs() -> Slot::OutputList*
        {
            return this->m_vectorOutputs;
        }

        auto Controller::getPointsetOutputs() -> Slot::OutputList*
        {
            return this->m_pointsetOutputs;
        }
        
        auto Controller::setStackSize(int stackSize) -> void
        {
            log_trace(Log::Set, stackSize);

            if (this->m_stackSize != stackSize)
            {
                this->m_stackSize = stackSize;
                emit this->stackSizeChanged();
            }
        }

        auto Controller::getStackSize() -> int
        {
            return this->m_stackSize;
        }

        auto Controller::setStackIndex(int stackIndex) -> void
        {
            if (this->m_stackIndex != stackIndex)
            {
                this->m_stackIndex = stackIndex;
                emit this->stackIndexChanged();
            }
        }

        auto Controller::getStackIndex() -> int
        {
            return this->m_stackIndex;
        }

        auto Controller::incrementIndex() -> void
        {
            auto index = this->m_stackIndex + 1;

            if (index >= this->m_stackSize)
            {
                index = 0;
            }

            if (this->m_stackIndex != index)
            {
                this->m_stackIndex = index;
                emit this->stackIndexChanged();
            }
        }

        auto Controller::decrementIndex() -> void
        {
            auto index = this->m_stackIndex - 1;

            if (index < 0)
            {
                index = this->m_stackSize - 1;
            }

            if (this->m_stackIndex != index)
            {
                this->m_stackIndex = index;
                emit this->stackIndexChanged();
            }
        }

        auto Controller::onNodeDataChanged() -> void
        {
            log_trace(Log::Func);

            if (this->m_node)
            {
                auto stackSize = 0;

                for (auto output : this->m_node->getOutputs())
                {
                    stackSize = std::max(output->getDataCount(), stackSize);
                }

                this->setStackSize(stackSize);
            }
        }

        auto Controller::setNode(Node::Object* node) -> void
        {
            log_trace(Log::Func, node);

            if (this->m_node == node)
            {
                return;
            }

            this->m_node = node;
            emit this->nodeChanged();

            if (!node)
            {
                setEmpty(true);
                return;
            }

            this->m_imageOutputs->clear();
            this->m_numberOutputs->clear();
            this->m_vectorOutputs->clear();
            this->m_pointsetOutputs->clear();

            auto stackSize = 0;

            for (auto output : node->getOutputs())
            {
                stackSize = std::max(output->getDataCount(), stackSize);

                if (output->getDataType() == Data::Type::Image)
                {
                    this->m_imageOutputs->addSlot(output);
                }
                else if (output->getDataType() == Data::Type::Number)
                {
                    this->m_numberOutputs->addSlot(output);
                }
                else if (output->getDataType() == Data::Type::Vector)
                {
                    this->m_vectorOutputs->addSlot(output);
                }
                else if (output->getDataType() == Data::Type::Pointset)
                {
                    this->m_pointsetOutputs->addSlot(output);
                }
            }

            this->setStackSize(stackSize);
            this->setStackIndex(0);
        }

        auto Controller::getNode() -> Node::Object*
        {
            return this->m_node;
        }

        auto Controller::reset() -> void
        {
            log_trace(Log::Func);

            if (this->m_node)
            {
                this->m_imageOutputs->clear();
                this->m_vectorOutputs->clear();
                this->m_numberOutputs->clear();
                this->m_pointsetOutputs->clear();

                this->m_node = nullptr;
                emit this->nodeChanged();

                this->setStackSize(0);
                this->setStackIndex(0);
            }
        }

        Controller::~Controller()
        {
            log_trace(Log::Del, this);
        }
    }
}
