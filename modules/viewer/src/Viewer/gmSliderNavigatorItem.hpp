#pragma once

#include "gmViewerExport.hpp"

#include <mitkStepper.h>

#include <QQuickItem>
#include <QString>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT SliderNavigatorItem: public QQuickItem
        {
            Q_OBJECT
            Q_PROPERTY(double min READ getMin WRITE setMin NOTIFY minChanged);
            Q_PROPERTY(double max READ getMax WRITE setMax NOTIFY maxChanged);
            Q_PROPERTY(double value READ getValue WRITE setValue NOTIFY valueChanged);
        private:
            double m_min;
            double m_max;
            double m_value;
            bool m_hasLabelUnit;
            bool m_maxValueValid;
            bool m_minValueValid;
            bool m_inRefetch;
            bool m_hasLabels;
            bool m_inverseDirection;
            float m_minValue;
            float m_maxValue;
            QString m_labelUnit;
            mitk::Stepper::Pointer m_stepper;
        public:
            SliderNavigatorItem(QQuickItem* parent = nullptr);
            ~SliderNavigatorItem();
            auto setMin(double min) -> void;
            auto setMax(double max) -> void;
            auto setValue(double value) -> void;
            auto getMin() -> double;
            auto getMax() -> double;
            auto getValue() -> double;
            auto getLabelUnit() -> QString;
            auto clippedValueToString(float value) -> QString;
            auto getMinValueLabel() -> QString;
            auto getMaxValueLabel() -> QString;
            auto getPos() -> int;
        public slots:
            void Refetch();
            void SetStepper( mitk::Stepper * stepper);
            void showLabels( bool show );
            void showLabelUnit( bool show );
            void setPos(int val);
            void setInverseDirection (bool inverseDirection);
        protected slots:
            void setLabelValues( float min, float max );
            void setLabelValuesValid( bool minValid, bool maxValid );
            void setLabelUnit( const char *unit );
        signals:
            void minChanged();
            void maxChanged();
            void valueChanged();
            void sync();
        };
    }
}


