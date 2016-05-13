#pragma once

#include "gmLog.hpp"

#include "gmParamNumber.hpp"
#include "gmParamOption.hpp"
#include "gmParamBool.hpp"
#include "gmParamString.hpp"
#include "gmParamDir.hpp"
#include "gmParamFiles.hpp"
#include "gmParamVector.hpp"

#include "gmSlotInput.hpp"
#include "gmSlotOutput.hpp"

#include "gmSlotIterator.hpp"
#include "gmLogicRegister.hpp"

#include "gmImageConvert.hpp"

namespace gm
{
    namespace Node
    {
        class Object;
    }
    
    namespace Slot
    {
        class InputList;
        class OutputList;
    }
    
    namespace Component
    {
        class Base;
    };
    
    namespace Logic
    {        
        class GM_CORE_EXPORT Base
        {
        private:
            unsigned int m_iteration;
            unsigned int m_iterations;
            Node::Object* m_node;
            QString m_docLink;
            QString m_name;
            QString m_lib;
        private:
            auto linkComponent(Component::Base*) -> void;
        public:
            Base(const QString&, const QString&);
            virtual auto run() -> void = 0;
            auto addParamGroup(const QString&) -> void;
            auto getNode() -> Node::Object*;
            auto getInputs() -> QList<Slot::InputBase*>;
            auto getOutputs() -> QList<Slot::OutputBase*>;
            auto setDocLink(const QString&) -> void;
            auto getDocLink() -> QString;
            auto setRunnable(bool) -> void;
            auto setUseTimer(bool) -> void;
            auto setThreaded(bool) -> void;
            auto setForceExecution(bool) -> void;
            auto setIsDataSource(bool) -> void;
            auto getName() -> QString;
            auto getLib() -> QString;
            auto execute() -> void;
            auto inputIterator() -> QList<Slot::Iterator>;
            auto add(Param::Base*) -> void;
            auto add(Slot::InputBase*) -> void;
            auto add(Slot::OutputBase*) -> void;
            auto getComponent(const QString&) -> Component::Base*;
            auto getInputBase(const QString&) -> Slot::InputBase*;
            auto getOutputBase(const QString&) -> Slot::OutputBase*;
            template <class TParam> auto getParam(const QString&) -> TParam*;
            template <class TData> auto getInput(const QString&) -> gm::Slot::Input<TData>*;
            template <class TData> auto getOutput(const QString&) -> gm::Slot::Output<TData>*;
            virtual ~Base();
        };
    }
}