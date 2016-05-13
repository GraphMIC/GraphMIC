#pragma once
#include "gmViewerExport.hpp"
#include "gmTransferFunctionCanvas.hpp"

#include <vtkColorTransferFunction.h>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT ColorTransferFunctionCanvas: public TransferFunctionCanvas
        {
            Q_OBJECT
            Q_PROPERTY(double greyValue READ getGreyValue WRITE setGreyValue)
        private:
            vtkColorTransferFunction* m_ColorTransferFunction;
            QString                   m_Title;
            double                    m_GreyValue;
        public:
            ColorTransferFunctionCanvas(QQuickPaintedItem* parent = nullptr);
            ~ColorTransferFunctionCanvas();
            virtual auto paint(QPainter* painter ) -> void override;
            auto setTitle(const QString &title) -> void;
            auto setColorTransferFunction(vtkColorTransferFunction* colorTransferFunction) -> void;
            auto setGreyValue(double value) -> void;
            auto getGreyValue() -> double;
            auto addRGB(double x, double r, double g, double b) -> void;
            auto doubleClickOnHandle(int handle) -> void;
            auto getNearHandle(int x,int y, unsigned int maxSquaredDistance = 32) -> int;
            auto addFunctionPoint(double x, double) -> int;
            auto moveFunctionPoint(int index, std::pair<double,double> pos) -> void;
            auto removeFunctionPoint(double x) -> void;
            auto removeAllFunctionPoints() -> void;
            auto getFunctionMax() -> double;
            auto getFunctionMin() -> double;
            auto getFunctionX(int index) -> double;
            auto getFunctionY(int) -> double;
            auto getFunctionSize() -> int;
            auto getFunctionRange() -> double;
        signals:
            void sync();
        };
    }
}

