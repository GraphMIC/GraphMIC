#include "gmLogicBase.hpp"
#include "gmNodeObject.hpp"

#include "gmParamGroup.hpp"
#include "gmParamGroupList.hpp"

#include "gmSlotInput.hpp"
#include "gmSlotOutput.hpp"
#include "gmSlotInputList.hpp"
#include "gmSlotOutputList.hpp"

#include "gmDebugController.hpp"

namespace gm
{
    namespace Logic
    {
        Base::Base(const QString& lib, const QString& name) : m_name(name), m_lib(lib)
        {
            this->m_node = new Node::Object(this);
            Debug::Controller::instance->incLogicCount();
        }

        auto Base::setDocLink(const QString& docLink) -> void
        {
            this->m_docLink = docLink;
        }

        auto Base::getDocLink() -> QString
        {
            return this->m_docLink;
        }
        
        auto Base::linkComponent(Component::Base* component) -> void
        {
            auto key = component->getName();
            this->m_node->m_components[key] = component;
            component->setNode(this->m_node);
        }
        
        auto Base::add(Slot::InputBase* input) -> void
        {
            this->linkComponent(input);
            this->m_node->m_inputList->addSlot(input);
        }
        
        auto Base::add(Slot::OutputBase* output) -> void
        {
            this->linkComponent(output);
            this->m_node->m_outputList->addSlot(output);
        }
        
        auto Base::add(Param::Base* param) -> void
        {
            this->linkComponent(param);
            this->m_node->getGroupList()->addParam(param);
        }
        
        auto Base::getNode() -> Node::Object*
        {
            return this->m_node;
        }
        
        auto Base::setRunnable(bool runnable) -> void
        {
            this->m_node->setRunnable(runnable);
        }
        
        auto Base::setUseTimer(bool useTimer) -> void
        {
            this->m_node->setUseTimer(useTimer);
        }
        
        auto Base::setThreaded(bool threaded) -> void
        {
            this->m_node->setThreaded(threaded);
        }
        
        template <class R>
        auto Base::getParam(const QString& key) -> R*
        {
            auto param = this->m_node->m_groupList->getParam(key);
            
            if (!param)
            {
                throw new std::runtime_error("could not find component with id \'" + key.toStdString() + "\'");
            }
            
            if (param->getComponentType() != R::ComponentType)
            {
                throw new std::runtime_error("requested component of type \'" + Component::StringFromType(param->getComponentType()).toStdString() + "\' - found component of type \'" + Component::StringFromType(R::ComponentType).toStdString() + " for component \'" + key.toStdString() + "\'");
            }
            
            return this->m_node->m_groupList->getParam(key)->as<R>();
        }
        
        auto Base::getComponent(const QString& key) -> Component::Base*
        {
            if (this->m_node->m_components.contains(key))
            {
                return this->m_node->m_components.value(key);
            }
            
            return nullptr;
        }

        template <class TData>
        auto Base::getInput(const QString& key) -> Slot::Input<TData>*
        {
            auto input = this->m_node->m_inputList->getSlot(key);

            if (input->getDataType() == TData::DataType)
            {
                return reinterpret_cast<Slot::Input<TData>*>(input);
            }

            return nullptr;
        }

        template <class TData>
        auto Base::getOutput(const QString& key) -> Slot::Output<TData>*
        {
            auto output = this->m_node->m_outputList->getSlot(key);

            if (output->getDataType() == TData::DataType)
            {
                return reinterpret_cast<Slot::Output<TData>*>(output);
            }

            return nullptr;
        }
        
        auto Base::getName() -> QString
        {
            return this->m_name;
        }
        
        auto Base::getLib() -> QString
        {
            return this->m_lib;
        }
        
        auto Base::getInputs() -> QList<Slot::InputBase*>
        {
            return this->m_node->m_inputList->getSlots();
        }
        
        auto Base::getOutputs() -> QList<Slot::OutputBase*>
        {
            return this->m_node->m_outputList->getSlots();
        }

        auto Base::getInputBase(const QString& key) -> Slot::InputBase*
        {
            return this->m_node->m_inputList->getSlot(key);
        }

        auto Base::getOutputBase(const QString& key) -> Slot::OutputBase*
        {
            return this->m_node->m_outputList->getSlot(key);
        }

        auto Base::inputIterator() -> QList<Slot::Iterator>
        {
            log_trace(Log::Func);

            this->m_iteration = 0;

            QList<gm::Slot::InputBase*> inputs;

            int stackSize = -1;

            auto slotList = this->m_node->m_inputList->getSlots();

            for (auto slot : slotList)
            {
                if (slot->getDataType() == Data::Type::Image)
                {
                    if (auto mockDataCount = slot->getMockData().count())
                    {
                        if (stackSize < 0)
                        {
                            stackSize = mockDataCount;
                        }

                        else if (stackSize != mockDataCount)
                        {
                            throw new std::runtime_error("data array length not consistent.");
                        }
                    }
                    if (auto output = slot->getOutput())
                    {
                        if (stackSize < 0)
                        {
                            stackSize = output->getDataCount();
                        }

                        else if (stackSize != output->getDataCount())
                        {
                            throw new std::runtime_error("data array length not consistent.");
                        }
                    }
                }

                inputs.append(slot);
            }

            this->m_iterations = stackSize;

            QList<Slot::Iterator> list;

            for (auto i = 0; i < stackSize; ++i)
            {
                list.push_back(Slot::Iterator(inputs, i));
            }

            return list;
        }
        
        auto Base::setIsDataSource(bool isDataSource) -> void
        {
            this->m_node->setIsDataSource(isDataSource);
        }
        
        auto Base::addParamGroup(const QString& group) -> void
        {
            this->m_node->m_groupList->addGroup(group);
        }

        auto Base::setForceExecution(bool forceExecution) -> void
        {
            this->m_node->setForceExecution(forceExecution);
        }

        Base::~Base()
        {
            Debug::Controller::instance->decLogicCount();
        }
        
        template auto Base::getInput<Data::Image>(const QString&) -> Slot::Input<Data::Image>*;
        template auto Base::getInput<Data::Vector>(const QString&) -> Slot::Input<Data::Vector>*;
        template auto Base::getInput<Data::Number>(const QString&) -> Slot::Input<Data::Number>*;
        template auto Base::getInput<Data::Pointset>(const QString&) -> Slot::Input<Data::Pointset>*;

        template auto Base::getOutput<Data::Image>(const QString&) -> Slot::Output<Data::Image>*;
        template auto Base::getOutput<Data::Vector>(const QString&) -> Slot::Output<Data::Vector>*;
        template auto Base::getOutput<Data::Number>(const QString&) -> Slot::Output<Data::Number>*;
        template auto Base::getOutput<Data::Pointset>(const QString&) -> Slot::Output<Data::Pointset>*;

        template auto Base::getParam<Param::Option>(const QString&) -> Param::Option*;
        template auto Base::getParam<Param::String>(const QString&) -> Param::String*;
        template auto Base::getParam<Param::Vector>(const QString&) -> Param::Vector*;
        template auto Base::getParam<Param::Number>(const QString&) -> Param::Number*;
        template auto Base::getParam<Param::Files>(const QString&) -> Param::Files*;
        template auto Base::getParam<Param::Bool>(const QString&) -> Param::Bool*;
        template auto Base::getParam<Param::Dir>(const QString&) -> Param::Dir*;
    }
}
