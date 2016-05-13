#pragma once
#define US_MODULE_NAME MeasurementItem

#include "gmViewerExport.hpp"
#include "gmViewItemBase.hpp"

#include <mitkEventConfig.h>
#include <mitkDataNode.h>
#include <mitkDataStorage.h>

#include "usServiceRegistration.h"

namespace mitk
{
    class PlanarFigure;
}

namespace gm
{
    namespace ViewItem
    {
        struct MeasurementViewData;
        class MeasurementItem: public ViewItemBase
        {
            Q_OBJECT
            Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged);
            Q_PROPERTY(QString infoText READ getInfoText WRITE setInfoText NOTIFY infoTextChanged);
        private:
            MeasurementViewData* d;
            std::map<us::ServiceReferenceU, mitk::EventConfig> m_DisplayInteractorConfigs;
            QString m_Text;
            QString m_InfoText;
        private:
            auto addFigureToDataStorage(mitk::PlanarFigure* figure, const QString &name) -> mitk::DataNode::Pointer;
            auto updateMeasurementText() -> void;
            auto addAllInteractors() -> void;
            auto removeAllInteractors() -> void;
            auto detectTopMostVisibleImage() -> mitk::DataNode::Pointer;
            auto enableCrosshairNavigation() -> void;
            auto disableCrosshairNavigation() -> void;
            auto planarFigureInitialized() -> void;
            auto getAllPlanarFigures() -> mitk::DataStorage::SetOfObjects::ConstPointer const;
        public:
            MeasurementItem();
            ~MeasurementItem();
            static MeasurementItem* instance;
            auto onSelectionChanged(const QList<mitk::DataNode::Pointer> &nodes) -> void;
            auto planarFigureSelected(itk::Object* object, const itk::EventObject &) -> void;
            auto initNode(const mitk::DataNode* node) -> void;
            auto nodeChanged(const mitk::DataNode* node) -> void override;
            auto nodeRemoved(const mitk::DataNode* node) -> void override;
            auto setText(QString text) -> void;
            auto getText() -> QString;
            auto setInfoText(QString text) -> void;
            auto getInfoText() -> QString;
            auto setNodeProperties(mitk::DataNode::Pointer node) -> void;
        public slots:
            void actionDrawLineTriggered();
            void actionDrawPathTriggered();
            void actionDrawAngleTriggered();
            void actionDrawFourPointAngleTriggered();
            void actionDrawCircleTriggered();
            void actionDrawEllipseTriggered();
            void actionDrawDoubleEllipseTriggered();
            void actionDrawRectangleTriggered();
            void actionDrawPolygonTriggered();
            void actionDrawBezierCurveTriggered();
            void actionDrawSubdivisionPolygonTriggered();
            void receive(mitk::DataNode::Pointer node);
        signals:
            void textChanged();
            void infoTextChanged();
            void setStatus(bool status);
        };
    }
}
