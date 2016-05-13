#pragma once

#include "gmViewerExport.hpp"

#include <gmRenderWindowItem.hpp>
#include <gmSliderNavigatorItem.hpp>

#include <mitkVector.h>
#include <QQuickitem>

namespace gm
{
    namespace ViewItem
    {
        class StepperAdapter;
        
        class GM_VIEWER_EXPORT ImageNavigator: public QQuickItem
        {
            Q_OBJECT
            Q_PROPERTY(SliderNavigatorItem* navigatorAxial READ getNavigatorAxial WRITE setNavigatorAxial)
            Q_PROPERTY(SliderNavigatorItem* navigatorSagittal READ getNavigatorSagittal WRITE setNavigatorSagittal)
            Q_PROPERTY(SliderNavigatorItem* navigatorCoronal READ getNavigatorCoronal WRITE setNavigatorCoronal)
            Q_PROPERTY(SliderNavigatorItem* navigatorTime READ getNavigatorTime WRITE setNavigatorTime)
            Q_PROPERTY(double worldCoordinateX READ getWorldCoordinateX WRITE setWorldCoordinateX)
            Q_PROPERTY(double worldCoordinateY READ getWorldCoordinateY WRITE setWorldCoordinateY)
            Q_PROPERTY(double worldCoordinateZ READ getWorldCoordinateZ WRITE setWorldCoordinateZ)
            Q_PROPERTY(double worldCoordinateXMin READ getWorldCoordinateXMin WRITE setWorldCoordinateXMin)
            Q_PROPERTY(double worldCoordinateYMin READ getWorldCoordinateYMin WRITE setWorldCoordinateYMin)
            Q_PROPERTY(double worldCoordinateZMin READ getWorldCoordinateZMin WRITE setWorldCoordinateZMin)
            Q_PROPERTY(double worldCoordinateXMax READ getWorldCoordinateXMax WRITE setWorldCoordinateXMax)
            Q_PROPERTY(double worldCoordinateYMax READ getWorldCoordinateYMax WRITE setWorldCoordinateYMax)
            Q_PROPERTY(double worldCoordinateZMax READ getWorldCoordinateZMax WRITE setWorldCoordinateZMax)
        private:
            SliderNavigatorItem* m_NavigatorAxial;
            SliderNavigatorItem* m_NavigatorSagittal;
            SliderNavigatorItem* m_NavigatorCoronal;
            SliderNavigatorItem* m_NavigatorTime;
            StepperAdapter* m_AxialStepper;
            StepperAdapter* m_SagittalStepper;
            StepperAdapter* m_FrontalStepper;
            StepperAdapter* m_TimeStepper;
            double m_WorldCoordinateX;
            double m_WorldCoordinateY;
            double m_WorldCoordinateZ;
            double m_WorldCoordinateXMin;
            double m_WorldCoordinateYMin;
            double m_WorldCoordinateZMin;
            double m_WorldCoordinateXMax;
            double m_WorldCoordinateYMax;
            double m_WorldCoordinateZMax;
        public:
            static ImageNavigator* instance;
        protected:
            auto setStepSizes() -> void;
            auto setStepSize(int axis) -> void;
            auto setStepSize(int axis, double stepSize) -> void;
            auto getClosestAxisIndex(mitk::Vector3D normal) -> int;
        public:
            ImageNavigator();
            ~ImageNavigator();
            auto setNavigatorAxial(SliderNavigatorItem* item) -> void;
            auto setNavigatorSagittal(SliderNavigatorItem* item) -> void;
            auto setNavigatorCoronal(SliderNavigatorItem* item) -> void;
            auto setNavigatorTime(SliderNavigatorItem* item) -> void;
            auto getNavigatorAxial() -> SliderNavigatorItem*;
            auto getNavigatorSagittal() -> SliderNavigatorItem*;
            auto getNavigatorCoronal() -> SliderNavigatorItem*;
            auto getNavigatorTime() -> SliderNavigatorItem*;
            auto setWorldCoordinateX(double coordinate) -> void;
            auto setWorldCoordinateY(double coordinate) -> void;
            auto setWorldCoordinateZ(double coordinate) -> void;
            auto setWorldCoordinateXMin(double coordinate) -> void;
            auto setWorldCoordinateYMin(double coordinate) -> void;
            auto setWorldCoordinateZMin(double coordinate) -> void;
            auto setWorldCoordinateXMax(double coordinate) -> void;
            auto setWorldCoordinateYMax(double coordinate) -> void;
            auto setWorldCoordinateZMax(double coordinate) -> void;
            auto getWorldCoordinateX() -> double;
            auto getWorldCoordinateY() -> double;
            auto getWorldCoordinateZ() -> double;
            auto getWorldCoordinateXMin() -> double;
            auto getWorldCoordinateYMin() -> double;
            auto getWorldCoordinateZMin() -> double;
            auto getWorldCoordinateXMax() -> double;
            auto getWorldCoordinateYMax() -> double;
            auto getWorldCoordinateZMax() -> double;
        public slots:
            void initialize();
            void onMillimetreCoordinateValueChanged();
            void onRefetch();
        signals:
            void sync();
        };
    }
}
