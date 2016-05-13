#pragma once

#include "gmPiecewiseFunctionCanvas.hpp"
#include "gmColorTransferFunctionCanvas.hpp"
#include "gmViewerExport.hpp"

#include <mitkCommon.h>
#include <mitkDataNode.h>
#include <mitkTransferFunctionProperty.h>

#include <QQuickItem>

namespace mitk
{
    class BaseRenderer;
}

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT TransferFunctionItem: public QQuickItem
        {
            Q_OBJECT
            Q_PROPERTY(PiecewiseFunctionCanvas* opacityItem READ getOpacityItem WRITE setOpactityItem);
            Q_PROPERTY(ColorTransferFunctionCanvas* colorItem READ getColorItem WRITE setColorItem);
            Q_PROPERTY(double min READ getMin WRITE setMin NOTIFY minChanged);
            Q_PROPERTY(double max READ getMax WRITE setMax NOTIFY maxChanged);
            Q_PROPERTY(double currentMin READ getCurrentMin WRITE setCurrentMin NOTIFY currentMinChanged);
            Q_PROPERTY(double currentMax READ getCurrentMax WRITE setCurrentMax NOTIFY currentMaxChanged);
        private:
            mitk::TransferFunctionProperty::Pointer tfpToChange;
            int m_min;
            int m_max;
            int m_currentMin;
            int m_currentMax;
            ColorTransferFunctionCanvas* m_colorItem;
            PiecewiseFunctionCanvas*     m_opacityItem;
            mitk::SimpleHistogramCache   m_histogramCache;
        public:
            static TransferFunctionItem* instance;
        public:
            TransferFunctionItem(QQuickItem* parent = nullptr);
            ~TransferFunctionItem();
            auto setDataNode(mitk::DataNode* node, const mitk::BaseRenderer* renderer = nullptr) -> void;
            auto setOpactityItem(PiecewiseFunctionCanvas* item) -> void;
            auto setColorItem(ColorTransferFunctionCanvas* item) -> void;
            auto getOpacityItem() -> PiecewiseFunctionCanvas*;
            auto getColorItem() -> ColorTransferFunctionCanvas*;
            auto setMin(double min) -> void;
            auto setMax(double max) -> void;
            auto setCurrentMin(double currentMin) -> void;
            auto setCurrentMax(double currentMax) -> void;
            auto getMin() -> double;
            auto getMax() -> double;
            auto getCurrentMin() -> double;
            auto getCurrentMax() -> double;
        public slots:
            void onUpdateCanvas();
            void onResetSlider();
            void onSpanChanged(int lower, int upper);
            void wheelEvent(QWheelEvent* event) override;
            void receive(mitk::DataNode::Pointer node);
            void updateRanges();
        signals:
            void currentMinChanged();
            void currentMaxChanged();
            void minChanged();
            void maxChanged();
            void sync();
        };
    }
}