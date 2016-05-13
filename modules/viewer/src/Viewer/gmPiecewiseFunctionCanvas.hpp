#pragma once

#include "gmTransferFunctionCanvas.hpp"
#include "gmViewerExport.hpp"

#include <mitkTransferFunctionProperty.h>
#include <mitkDataNode.h>

#include <vtkPiecewiseFunction.h>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT PiecewiseFunctionCanvas: public TransferFunctionCanvas
        {
            Q_OBJECT
            Q_PROPERTY(double greyValue READ getGreyValue WRITE setGreyValue)
            Q_PROPERTY(double opacity READ getOpacity WRITE setOpacity)
        protected:
            vtkPiecewiseFunction* m_piecewiseFunction;
            QString m_title;
            double  m_greyValue;
            double  m_opacity;
        public:
            static PiecewiseFunctionCanvas* instance;
        public:
            PiecewiseFunctionCanvas(QQuickPaintedItem* parent = nullptr);
            ~PiecewiseFunctionCanvas();
            auto paint(QPainter* painter ) -> void override;
            auto setTitle(const QString& title) -> void;
            auto setGreyValue(double value) -> void;
            auto getGreyValue() -> double;
            auto setOpacity(double opacity) -> void;
            auto getOpacity() -> double;
            auto setPiecewiseFunction(vtkPiecewiseFunction* piecewiseFunction) -> void;
            virtual auto getNearHandle(int x,int y,unsigned int maxSquaredDistance = 32) -> int;
            virtual auto addFunctionPoint(double x,double val) -> int;
            virtual auto removeFunctionPoint(double x) -> void;
            virtual auto getFunctionX(int index) -> double;
            virtual auto getFunctionY(int index) -> double;
            auto getFunctionSize() -> int;
            auto doubleClickOnHandle(int) -> void;
            auto moveFunctionPoint(int index, std::pair<double,double> pos) -> void;
            auto getFunctionMax() -> double;
            auto getFunctionMin() -> double;
            auto getFunctionRange() -> double;
            auto removeAllFunctionPoints() -> void;
            auto resetGO() -> void;
            auto mousePressEvent( QMouseEvent* mouseEvent ) -> void override;
            auto mouseMoveEvent( QMouseEvent* mouseEvent ) -> void override;
            auto mouseReleaseEvent( QMouseEvent* mouseEvent ) -> void override;
            auto mouseDoubleClickEvent( QMouseEvent* mouseEvent ) -> void override;
            auto keyPressEvent(QKeyEvent* keyEvent) -> void override;
        signals:
            void sync();
        };
    }
}

