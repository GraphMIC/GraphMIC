#pragma once

#include "gmNodeSelectable.hpp"

#include <QObject>

namespace gm
{
    namespace Slot
    {
        class InputBase;
        class OutputBase;
    }
    
    namespace Connection
    {
        class View;
        class Object;
        
        auto Create(Slot::OutputBase*, Slot::InputBase*) -> void;
        auto Delete(Object*) -> void;
        
        class Object : public Node::Selectable
        {
            Q_OBJECT
            Q_PROPERTY(bool valid READ getValid NOTIFY validChanged);
            Q_PROPERTY(gm::Slot::InputBase* input READ getInput CONSTANT);
            Q_PROPERTY(bool hasData READ getHasData NOTIFY hasDataChanged);
            Q_PROPERTY(gm::Slot::OutputBase* output READ getOutput CONSTANT);
            Q_PROPERTY(gm::Connection::View* view READ getView WRITE setView NOTIFY viewChanged);
        private:
            friend auto Create(Slot::OutputBase*, Slot::InputBase*) -> void;
            friend auto Delete(Object*) -> void;
        private:
            Slot::OutputBase* m_output;
            Slot::InputBase* m_input;
            bool m_hasData;
            View* m_view;
            bool m_valid;
            int m_offset;
            Object(Slot::OutputBase*, Slot::InputBase*);
        public:
            auto setView(View*) -> void;
            auto getView() -> View*;
            auto setValid(bool) -> void;
            auto getValid() -> bool;
            auto setHasData(bool) -> void;
            auto getHasData() -> bool;
            auto getOutput() -> Slot::OutputBase*;
            auto getInput() -> Slot::InputBase*;
            auto updateView() -> void;
            auto deleteObject() -> void override;
            ~Object();
        signals:
            void hasDataChanged();
            void validChanged();
            void viewChanged();
        };
    }
}
