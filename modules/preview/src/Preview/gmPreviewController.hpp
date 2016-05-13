#pragma once

#include "gmPreviewExport.hpp"
#include "gmInterfacePreviewController.hpp"

namespace gm
{
    namespace Node
    {
        class Object;
    };

    namespace Slot
    {
        class OutputList;
    }

    namespace Preview
    {
        class GM_PREVIEW_EXPORT Controller : public Interface::Preview::Controller
        {
            Q_OBJECT
            Q_PROPERTY(gm::Node::Object* node READ getNode NOTIFY nodeChanged);
            Q_PROPERTY(gm::Slot::OutputList* imageOutputs READ getImageOutputs CONSTANT);
            Q_PROPERTY(gm::Slot::OutputList* numberOutputs READ getNumberOutputs CONSTANT);
            Q_PROPERTY(gm::Slot::OutputList* vectorOutputs READ getVectorOutputs CONSTANT);
            Q_PROPERTY(gm::Slot::OutputList* pointsetOutputs READ getPointsetOutputs CONSTANT);
            Q_PROPERTY(bool empty READ getEmpty NOTIFY emptyChanged);
            Q_PROPERTY(int stackIndex READ getStackIndex NOTIFY stackIndexChanged);
            Q_PROPERTY(int stackSize READ getStackSize NOTIFY stackSizeChanged);
        public:
            Slot::OutputList* m_pointsetOutputs;
            Slot::OutputList* m_numberOutputs;
            Slot::OutputList* m_vectorOutputs;
            Slot::OutputList* m_imageOutputs;
            Node::Object* m_node;
            bool m_empty;
            int m_stackSize;
            int m_stackIndex;
            static Controller* instance;
        private:
            auto setEmpty(bool) -> void;
        public:
            Controller();
            auto setNode(Node::Object*) -> void override;
            auto getNode() -> Node::Object* override;
            auto reset() -> void override;
            auto getEmpty() -> bool;
            auto getImageOutputs() -> Slot::OutputList*;
            auto getNumberOutputs() -> Slot::OutputList*;
            auto getVectorOutputs() -> Slot::OutputList*;
            auto getPointsetOutputs() -> Slot::OutputList*;
            auto setStackSize(int) -> void;
            auto getStackSize() -> int;
            auto setStackIndex(int) -> void;
            auto getStackIndex() -> int;
            auto releaseNode() -> void;
            auto onNodeDataChanged() -> void override;
            static auto Create() -> Controller*;
            ~Controller();
        public slots:
            void incrementIndex();
            void decrementIndex();
        signals:
            void stackIndexChanged();
            void stackSizeChanged();
            void emptyChanged();
            void nodeChanged();
        };
    }
}
