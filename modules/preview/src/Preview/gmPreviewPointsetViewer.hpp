#pragma once

#include "gmPreviewExport.hpp"

#include <QObject>

namespace gm
{
    namespace Data
    {
        class Pointset;
    }

    namespace Slot
    {
        class OutputBase;
    }

    namespace Preview
    {
        class GM_PREVIEW_EXPORT PointsetViewer : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(gm::Slot::OutputBase* output READ getOutput WRITE setOutput NOTIFY outputChanged);
            Q_PROPERTY(gm::Data::Pointset* pointset READ getPointset NOTIFY pointsetChanged);
            Q_PROPERTY(int stackIndex READ getStackIndex NOTIFY stackIndexChanged);
            Q_PROPERTY(int stackSize READ getStackSize NOTIFY stackSizeChanged);
        private:
            Slot::OutputBase* m_output;
            Data::Pointset* m_pointset;
            int m_stackIndex;
            int m_stackSize;
        private:
            auto setOutput(Slot::OutputBase*) -> void;
            auto getOutput() -> Slot::OutputBase*;
            auto setPointset(Data::Pointset*) -> void;
            auto getPointset() -> Data::Pointset*;
            auto setStackIndex(int) -> void;
            auto getStackIndex() -> int;
            auto setStackSize(int) -> void;
            auto getStackSize() -> int;
            auto updateData() -> void;
        public:
            PointsetViewer();
            ~PointsetViewer();
        signals:
            void stackIndexChanged();
            void stackSizeChanged();
            void outputChanged();
            void pointsetChanged();
        };
    }
}