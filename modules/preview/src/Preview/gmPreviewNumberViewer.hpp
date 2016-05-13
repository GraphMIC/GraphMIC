#pragma once

#include "gmPreviewExport.hpp"

#include <QObject>

namespace gm
{
    namespace Data
    {
        class Number;
    }

    namespace Slot
    {
        class OutputBase;
    }

    namespace Preview
    {
        class GM_PREVIEW_EXPORT NumberViewer : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(gm::Slot::OutputBase* output READ getOutput WRITE setOutput NOTIFY outputChanged);
            Q_PROPERTY(gm::Data::Number* number READ getNumber NOTIFY numberChanged);
            Q_PROPERTY(int stackIndex READ getStackIndex NOTIFY stackIndexChanged);
            Q_PROPERTY(int stackSize READ getStackSize NOTIFY stackSizeChanged);
        private:
            Slot::OutputBase* m_output;
            Data::Number* m_number;
            int m_stackIndex;
            int m_stackSize;
        private:
            auto setOutput(Slot::OutputBase*) -> void;
            auto getOutput() -> Slot::OutputBase*;
            auto setNumber(Data::Number*) -> void;
            auto getNumber() -> Data::Number*;
            auto setStackIndex(int) -> void;
            auto getStackIndex() -> int;
            auto setStackSize(int) -> void;
            auto getStackSize() -> int;
            auto updateData() -> void;
        public:
            NumberViewer();
            ~NumberViewer();
        signals:
            void stackIndexChanged();
            void stackSizeChanged();
            void outputChanged();
            void numberChanged();
        };
    }
}