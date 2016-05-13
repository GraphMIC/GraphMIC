#pragma once

#include "gmViewerExport.hpp"
#include "gmImageStatisticsCalculationThread.hpp"
#include "gmStepperAdapter.hpp"
#include "gmHistogramItem.hpp"
#include "gmViewItemBase.hpp"
#include <mitkImageStatisticsCalculator.h>
#include <mitkPlanarLine.h>
#include <mitkDataStorage.h>
#include <QQuickItem>
#include <QFutureWatcher>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT ImageStatisticsItem: public ViewItemBase
        {
            Q_OBJECT
            Q_PROPERTY(int binSize READ getBinSize WRITE setBinSize NOTIFY binSizeChanged);
            Q_PROPERTY(bool defaultBinSize READ isDefaultBinSize WRITE setDefaultBinSize NOTIFY defaultBinSizeChanged);
            Q_PROPERTY(bool spinBoxStatus READ getSpinBoxStatus WRITE setSpinBoxStatus NOTIFY spinBoxStatusChanged);
            Q_PROPERTY(bool ignoreZeroValues READ isIgnoreZeroValues WRITE setIgnoreZeroValues);
            Q_PROPERTY(QString histogramInfo READ getHistogramInfo WRITE setHistogramInfo NOTIFY histogramInfoChanged);
            Q_PROPERTY(gm::ViewItem::HistogramItem* histogramItem READ getHistogramItem WRITE setHistogramItem);
        private:
            typedef mitk::DataStorage::SetOfObjects  ConstVector;
            typedef QList<mitk::DataNode*>           SelectedDataNodeVectorType;
            typedef itk::SimpleMemberCommand<ImageStatisticsItem> ITKCommandType;
            HistogramItem*              m_histogramItem;
            QFutureWatcher<void>*       m_futureWatcher;
            mitk::DataNode::Pointer     m_node;
            mitk::DataStorage::Pointer  m_dataStorage;
            StepperAdapter*             m_timeStepperAdapter;
            QString                     m_histogramInfo;
            mitk::Image*                m_selectedImage;
            mitk::Image*                m_selectedImageMask;
            mitk::PlanarFigure*         m_selectedPlanarFigure;
            SelectedDataNodeVectorType  m_selectedDataNodes;
            std::vector<mitk::Point3D>  m_worldMinList;
            std::vector<mitk::Point3D>  m_worldMaxList;
            int  m_binSize;
            long m_imageObserverTag;
            long m_imageMaskObserverTag;
            long m_planarFigureObserverTag;
            long m_timeObserverTag;
            bool m_defaultBinSize;
            bool m_spinBoxStatus;
            bool m_ignoreZeroValues;
            bool m_currentStatisticsValid;
            bool m_statisticsUpdatePending;
            bool m_dataNodeSelectionChanged;
            bool m_visible;
            ImageStatisticsCalculation* m_calculationThread;
        public:
            static ImageStatisticsItem* instance;
        protected:
            auto fillStatisticsTableView(const std::vector<mitk::ImageStatisticsCalculator::Statistics> &s, const mitk::Image* image) -> void;
            auto invalidateStatisticsTableView() -> void;
            auto updateStatistics() -> void;
            auto selectedDataModified() -> void;
            auto selectionChanged(const QList<mitk::DataNode::Pointer> &selectedNodes) -> void;
            auto reinitData() -> void;
            auto writeStatisticsToGUI() -> void;
            auto nodeRemoved(const mitk::DataNode* node) -> void;
        public:
            ImageStatisticsItem(QObject *parent=nullptr, const char *name=nullptr);
            virtual ~ImageStatisticsItem();
            auto setHistogramInfo(QString info) -> void;
            auto getHistogramInfo() -> QString;
            auto setBinSize(int size) -> void;
            auto getBinSize() -> int;
            auto isDefaultBinSize() -> bool;
            auto setDefaultBinSize(bool status) -> void;
            auto getSpinBoxStatus() -> bool;
            auto setSpinBoxStatus(bool status) -> void;
            auto setHistogramItem(HistogramItem* item) -> void;
            auto getHistogramItem() -> HistogramItem*;
            auto setIgnoreZeroValues(bool status) -> void;
            auto isIgnoreZeroValues() -> bool;
        public slots:
            void onThreadedStatisticsCalculationEnds();
            void computeStatistics();
            void requestStatisticsUpdate();
            void receive(mitk::DataNode::Pointer node);
        signals:
            void statisticsUpdate();
            void binSizeChanged();
            void defaultBinSizeChanged();
            void spinBoxStatusChanged();
            void setStatus(bool status);
            void histogramInfoChanged();
        };
    }
}
