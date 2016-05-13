#pragma once

#include "gmViewerExport.hpp"

#include <mitkSimpleHistogram.h>
#include <mitkRenderingManager.h>

#include <QQuickPaintedItem>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT TransferFunctionCanvas : public QQuickPaintedItem
        {
            Q_OBJECT
        private:
            bool    m_immediateUpdate;
            float   m_range;
            double  m_lower;
            double  m_upper;
            mitk::SimpleHistogram* m_histogram;
        protected:
            double  m_min;
            double  m_max;
            int     m_grabbedHandle;
        public:
            TransferFunctionCanvas(QQuickPaintedItem *parent = nullptr);
            ~TransferFunctionCanvas();
            auto setX(float x) -> void;
            auto setY(float y) -> void;
            auto setHistogram(mitk::SimpleHistogram *histogram) -> void;
            auto setMin(double min) -> void;
            auto setMax(double max) -> void;
            auto setLower(double lower) -> void;
            auto setUpper(double upper) -> void;
            auto getUpper() -> double;
            auto getMin() -> double;
            auto getMax() -> double;
            auto getLower() -> double;
            auto getHistogram() -> mitk::SimpleHistogram*;
            auto mousePressEvent(QMouseEvent *mouseEvent) -> void override;
            auto mouseMoveEvent(QMouseEvent *mouseEvent) -> void override;
            auto mouseReleaseEvent(QMouseEvent *mouseEvent) -> void override;
            auto mouseDoubleClickEvent(QMouseEvent *mouseEvent) -> void override;
            auto keyPressEvent(QKeyEvent *event) -> void override;
            auto paintHistogram(QPainter *painter) -> void;
            auto functionToCanvas(std::pair<double, double>) -> std::pair<int, int>;
            auto canvasToFunction(std::pair<int, int>) -> std::pair<double, double>;
            auto setImmediateUpdate(bool state) -> void;
            auto validateCoord(std::pair<double, double> x) -> std::pair<double, double>;
            virtual auto paint(QPainter *painter) -> void = 0;
            virtual auto doubleClickOnHandle(int handle) -> void = 0;
            virtual auto getNearHandle(int x, int y, unsigned int maxSquaredDistance = 32) -> int = 0;
            virtual auto addFunctionPoint(double x, double val) -> int = 0;
            virtual auto removeFunctionPoint(double x) -> void = 0;
            virtual auto moveFunctionPoint(int index, std::pair<double, double> pos) -> void = 0;
            virtual auto getFunctionX(int index) -> double = 0;
            virtual auto getFunctionY(int index) -> double = 0;
            virtual auto getFunctionSize() -> int = 0;
        };
    }
}



