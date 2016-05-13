#pragma once

#include "gmViewerExport.hpp"

#include <QQuickItem>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT PropertyController : public QQuickItem
        {
            Q_OBJECT
            Q_PROPERTY(bool volumeRendering READ getVolumeRendering WRITE setVolumeRendering NOTIFY volumeRenderingChanged);
            Q_PROPERTY(bool imageNavigator READ getImageNavigator WRITE setImageNavigator NOTIFY imageNavigatorChanged);
            Q_PROPERTY(bool measurement READ getMeasurement WRITE setMeasurement NOTIFY measurementChanged);
            Q_PROPERTY(bool pointSet READ getPointSet WRITE setPointSet NOTIFY pointSetChanged);
            Q_PROPERTY(bool masking READ getMasking WRITE setMasking NOTIFY maskingChanged);
            Q_PROPERTY(bool statistics READ getStatistics WRITE setStatistics NOTIFY statisticsChanged);
        private:
            bool m_volumeRendering;
            bool m_imageNavigator;
            bool m_measurement;
            bool m_pointSet;
            bool m_masking;
            bool m_statistics;
        public:
            static PropertyController* instance;
        public:
            PropertyController();
            ~PropertyController();
            auto getVolumeRendering() -> bool;
            auto getImageNavigator() -> bool;
            auto getMeasurement() -> bool;
            auto getPointSet() -> bool;
            auto getMasking() -> bool;
            auto getStatistics() -> bool;
        public slots:
            void setVolumeRendering(bool status);
            void setImageNavigator(bool status);
            void setMeasurement(bool status);
            void setPointSet(bool status);
            void setMasking(bool status);
            void setStatistics(bool status);
        signals:
            void volumeRenderingChanged();
            void imageNavigatorChanged();
            void measurementChanged();
            void pointSetChanged();
            void maskingChanged();
            void statisticsChanged();
        };
    }
}