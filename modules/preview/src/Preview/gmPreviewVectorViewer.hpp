#pragma once

#include "gmPreviewExport.hpp"

#include <QObject>

namespace gm
{
    namespace Data
    {
        class Vector;
    }

    namespace Slot
    {
        class OutputBase;
    }

    namespace Preview
    {
        class GM_PREVIEW_EXPORT VectorViewer : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(gm::Slot::OutputBase* output READ getOutput WRITE setOutput NOTIFY outputChanged);
            Q_PROPERTY(gm::Data::Vector* vector READ getVector NOTIFY vectorChanged);
            Q_PROPERTY(int stackIndex READ getStackIndex NOTIFY stackIndexChanged);
            Q_PROPERTY(int stackSize READ getStackSize NOTIFY stackSizeChanged);
        private:
            Slot::OutputBase* m_output;
            Data::Vector* m_vector;
            int m_stackIndex;
            int m_stackSize;
        private:
            auto setOutput(Slot::OutputBase*) -> void;
            auto getOutput() -> Slot::OutputBase*;
            auto setVector(Data::Vector*) -> void;
            auto getVector() -> Data::Vector*;
            auto setStackIndex(int) -> void;
            auto getStackIndex() -> int;
            auto setStackSize(int) -> void;
            auto getStackSize() -> int;
            auto updateData() -> void;
        public:
            VectorViewer();
            ~VectorViewer();
        signals:
            void stackIndexChanged();
            void stackSizeChanged();
            void outputChanged();
            void vectorChanged();
        };
    }
}