#include "gmMeasurementItem.hpp"

#include <mitkInteractionEventObserver.h>
#include <mitkIPropertyFilters.h>
#include <mitkPropertyFilter.h>
#include <mitkVtkLayerController.h>
#include <mitkWeakPointer.h>
#include <mitkPlanarCircle.h>
#include <mitkPlanarEllipse.h>
#include <mitkPlanarPolygon.h>
#include <mitkPlanarAngle.h>
#include <mitkPlanarRectangle.h>
#include <mitkPlanarLine.h>
#include <mitkPlanarCross.h>
#include <mitkPlanarFourPointAngle.h>
#include <mitkPlanarDoubleEllipse.h>
#include <mitkPlanarBezierCurve.h>
#include <mitkPlanarSubdivisionPolygon.h>
#include <mitkPlanarFigureInteractor.h>
#include <mitkNodePredicateDataType.h>
#include <mitkNodePredicateProperty.h>
#include <mitkNodePredicateAnd.h>
#include <mitkNodePredicateNot.h>
#include <mitkImage.h>
#include <mitkDisplayInteractor.h>
#include <mitkPointSet.h>
#include <mitkPointSetDataInteractor.h>
#include <usModuleRegistry.h>
#include <usGetModuleContext.h>
#include <usModuleInitialization.h>
#include "gmRenderWindowItem.hpp"
#include "gmStdMultiItem.hpp"
#include "gmDatamanager.hpp"
#include "gmPropertyController.hpp"

US_INITIALIZE_MODULE

namespace gm
{
    namespace ViewItem
    {
        MeasurementItem* MeasurementItem::instance = nullptr;

        class PlanarFigureData
        {
            public:
            PlanarFigureData() : m_Figure(0), m_EndPlacementObserverTag(0), m_SelectObserverTag(0), m_StartInteractionObserverTag(0), m_EndInteractionObserverTag(0)
            {
            }

            mitk::PlanarFigure* m_Figure;
            unsigned int m_EndPlacementObserverTag;
            unsigned int m_SelectObserverTag;
            unsigned int m_StartInteractionObserverTag;
            unsigned int m_EndInteractionObserverTag;
        };

        class MeasurementViewData
        {
            public:
            MeasurementViewData() : m_LineCounter(0), m_PathCounter(0), m_AngleCounter(0), m_FourPointAngleCounter(0), m_CircleCounter(0), m_EllipseCounter(0), m_DoubleEllipseCounter(0), m_RectangleCounter(0), m_PolygonCounter(0), m_BezierCurveCounter(0), m_SubdivisionPolygonCounter(0), m_UnintializedPlanarFigure(false), m_ScrollEnabled(true)
            {
            }

            unsigned int m_LineCounter;
            unsigned int m_PathCounter;
            unsigned int m_AngleCounter;
            unsigned int m_FourPointAngleCounter;
            unsigned int m_CircleCounter;
            unsigned int m_EllipseCounter;
            unsigned int m_DoubleEllipseCounter;
            unsigned int m_RectangleCounter;
            unsigned int m_PolygonCounter;
            unsigned int m_BezierCurveCounter;
            unsigned int m_SubdivisionPolygonCounter;
            QList<mitk::DataNode::Pointer> m_CurrentSelection;
            std::map<mitk::DataNode*, PlanarFigureData> m_DataNodeToPlanarFigureData;
            mitk::DataNode::Pointer m_SelectedImageNode;
            bool m_UnintializedPlanarFigure;
            bool m_ScrollEnabled;
        };

        MeasurementItem::MeasurementItem() : d(new MeasurementViewData())
        {
            if(instance)
            {
                throw ("instance already existing");
            }

            instance = this;

            this->addAllInteractors();
            this->setEnabled(false);

            connect(DataManager::instance, &DataManager::notifySelection, this, &MeasurementItem::receive);
            connect(this, &MeasurementItem::setStatus, PropertyController::instance, &PropertyController::setMeasurement);
        }

        MeasurementItem::~MeasurementItem()
        {
            this->removeAllInteractors();
            delete d;
        }

        void MeasurementItem::receive(mitk::DataNode::Pointer node)
        {
            if(!node)
            {
                setEnabled(false);
                emit this->setStatus(false);
                return;
            }

            bool isMeasurement = false;
            node->GetBoolProperty("measurement", isMeasurement);
            mitk::PlanarFigure* figure = dynamic_cast<mitk::PlanarFigure*>(node->GetData());

            if(isMeasurement && !figure)
            {
                emit this->setStatus(true);

                d->m_SelectedImageNode = node;
                this->setEnabled(true);
            }
            else if(figure)
            {
                QList<mitk::DataNode::Pointer> list;
                list.push_back(node);
                this->onSelectionChanged(list);

                emit this->setStatus(true);
                this->setEnabled(false);
            }
            else
            {
                emit this->setStatus(false);
                this->setEnabled(false);
            }
        }

        auto MeasurementItem::initNode(const mitk::DataNode* node) -> void
        {
            mitk::PlanarFigure* figure = dynamic_cast<mitk::PlanarFigure*>(node->GetData());
            bool isPositionMarker(false);
            node->GetBoolProperty("isContourMarker", isPositionMarker);
            if(figure && !isPositionMarker)
            {
                mitk::PlanarFigureInteractor::Pointer figureInteractor = dynamic_cast<mitk::PlanarFigureInteractor*>(node->GetDataInteractor().GetPointer());

                mitk::DataNode* nonConstNode = const_cast<mitk::DataNode*>( node );

                if(figureInteractor.IsNull())
                {
                    figureInteractor = mitk::PlanarFigureInteractor::New();
                    us::Module* planarFigureModule = us::ModuleRegistry::GetModule("MitkPlanarFigure");
                    figureInteractor->LoadStateMachine("PlanarFigureInteraction.xml", planarFigureModule);
                    figureInteractor->SetEventConfig("PlanarFigureConfig.xml", planarFigureModule);
                    figureInteractor->SetDataNode(nonConstNode);
                }

                PlanarFigureData data;
                data.m_Figure = figure;

                typedef itk::SimpleMemberCommand<MeasurementItem> SimpleCommandType;
                SimpleCommandType::Pointer initializationCommand = SimpleCommandType::New();
                initializationCommand->SetCallbackFunction(this, &MeasurementItem::planarFigureInitialized);
                data.m_EndPlacementObserverTag = figure->AddObserver(mitk::EndPlacementPlanarFigureEvent(), initializationCommand);

                typedef itk::MemberCommand<MeasurementItem> MemberCommandType;
                MemberCommandType::Pointer selectCommand = MemberCommandType::New();
                selectCommand->SetCallbackFunction(this, &MeasurementItem::planarFigureSelected);
                data.m_SelectObserverTag = figure->AddObserver(mitk::SelectPlanarFigureEvent(), selectCommand);

                SimpleCommandType::Pointer startInteractionCommand = SimpleCommandType::New();
                startInteractionCommand->SetCallbackFunction(this, &MeasurementItem::disableCrosshairNavigation);
                data.m_StartInteractionObserverTag = figure->AddObserver(mitk::StartInteractionPlanarFigureEvent(), startInteractionCommand);

                SimpleCommandType::Pointer endInteractionCommand = SimpleCommandType::New();
                endInteractionCommand->SetCallbackFunction(this, &MeasurementItem::enableCrosshairNavigation);
                data.m_EndInteractionObserverTag = figure->AddObserver(mitk::EndInteractionPlanarFigureEvent(), endInteractionCommand);

                d->m_DataNodeToPlanarFigureData[nonConstNode] = data;
            }
        }

        auto MeasurementItem::nodeChanged(const mitk::DataNode* node) -> void
        {
            bool renewText = false;
            for(int i = 0; i < d->m_CurrentSelection.size(); ++i)
            {
                if(node == d->m_CurrentSelection.at(i))
                {
                    renewText = true;
                    break;
                }
            }

            if(renewText)
            {
                this->updateMeasurementText();
            }
        }

        auto MeasurementItem::nodeRemoved(const mitk::DataNode* node) -> void
        {
            mitk::DataNode* nonConstNode = const_cast<mitk::DataNode*>(node);
            std::map<mitk::DataNode*, PlanarFigureData>::iterator it = d->m_DataNodeToPlanarFigureData.find(nonConstNode);

            bool isFigureFinished = false;
            bool isPlaced = false;

            if(it != d->m_DataNodeToPlanarFigureData.end())
            {
                PlanarFigureData &data = it->second;

                data.m_Figure->RemoveObserver(data.m_EndPlacementObserverTag);
                data.m_Figure->RemoveObserver(data.m_SelectObserverTag);
                data.m_Figure->RemoveObserver(data.m_StartInteractionObserverTag);
                data.m_Figure->RemoveObserver(data.m_EndInteractionObserverTag);

                isFigureFinished = data.m_Figure->GetPropertyList()->GetBoolProperty("initiallyplaced", isPlaced);
                if(!isFigureFinished)
                {
                    planarFigureInitialized();
                }
                d->m_DataNodeToPlanarFigureData.erase(it);
            }

            mitk::TNodePredicateDataType<mitk::PlanarFigure>::Pointer isPlanarFigure = mitk::TNodePredicateDataType<mitk::PlanarFigure>::New();

            mitk::DataStorage::SetOfObjects::ConstPointer nodes = storage->GetDerivations(node, isPlanarFigure);

            for(unsigned int x = 0; x < nodes->size(); x++)
            {
                mitk::PlanarFigure* planarFigure = dynamic_cast<mitk::PlanarFigure*>(nodes->at(x)->GetData());

                if(planarFigure != NULL)
                {
                    isFigureFinished = planarFigure->GetPropertyList()->GetBoolProperty("initiallyplaced", isPlaced);

                    if(!isFigureFinished)
                    {
                        storage->Remove(nodes->at(x));

                        if(!d->m_DataNodeToPlanarFigureData.empty())
                        {
                            std::map<mitk::DataNode*, PlanarFigureData>::iterator it2 = d->m_DataNodeToPlanarFigureData.find(nodes->at(x));

                            if(it2 != d->m_DataNodeToPlanarFigureData.end())
                            {
                                d->m_DataNodeToPlanarFigureData.erase(it2);
                                planarFigureInitialized();
                                enableCrosshairNavigation();
                            }
                        }
                    }
                }
            }
        }

        auto MeasurementItem::planarFigureSelected(itk::Object* object, const itk::EventObject &) -> void
        {
            std::map<mitk::DataNode*, PlanarFigureData>::iterator it = d->m_DataNodeToPlanarFigureData.begin();

            d->m_CurrentSelection.clear();
            while(it != d->m_DataNodeToPlanarFigureData.end())
            {
                mitk::DataNode* node = it->first;
                PlanarFigureData &data = it->second;

                if(data.m_Figure == object)
                {
                    MITK_DEBUG << "selected node found. enabling selection";
                    node->SetSelected(true);
                    DataManager::instance->setSelectedNode(node);
                    d->m_CurrentSelection.push_back(node);
                }
                else
                {
                    node->SetSelected(false);
                }

                ++it;
            }
            this->updateMeasurementText();
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }

        auto MeasurementItem::planarFigureInitialized() -> void
        {
            d->m_UnintializedPlanarFigure = false;
        }

        auto MeasurementItem::onSelectionChanged(const QList<mitk::DataNode::Pointer> &nodes) -> void
        {
            d->m_CurrentSelection = nodes;
            this->updateMeasurementText();

            if(d->m_CurrentSelection.size() == 0)
            {
                mitk::TNodePredicateDataType<mitk::PlanarFigure>::Pointer isPlanarFigure = mitk::TNodePredicateDataType<mitk::PlanarFigure>::New();
                mitk::DataStorage::SetOfObjects::ConstPointer planarFigures = storage->GetSubset(isPlanarFigure);

                for(mitk::DataStorage::SetOfObjects::ConstIterator it = planarFigures->Begin();
                    it != planarFigures->End(); it++)
                {
                    mitk::DataNode* node = it.Value();
                    bool isHelperObject(false);
                    node->GetBoolProperty("helper object", isHelperObject);
                    if(!isHelperObject)
                    {
                        node->SetSelected(false);
                    }
                }
            }

            for(int i = d->m_CurrentSelection.size() - 1; i >= 0; --i)
            {
                mitk::DataNode* node = d->m_CurrentSelection.at(i);
                mitk::PlanarFigure* _PlanarFigure = dynamic_cast<mitk::PlanarFigure*> (node->GetData());

                if(_PlanarFigure && _PlanarFigure->GetPlaneGeometry())
                {
                    RenderWindowItem* selectedRenderWindow = 0;
                    bool PlanarFigureInitializedWindow = false;

                    RenderWindowItem* RenderWindow1 = StdMultiItem::instance->getViewerAxial();
                    RenderWindowItem* RenderWindow2 = StdMultiItem::instance->getViewerSagittal();
                    RenderWindowItem* RenderWindow3 = StdMultiItem::instance->getViewerCoronal();
                    RenderWindowItem* RenderWindow4 = StdMultiItem::instance->getViewerOriginal();

                    if(node->GetBoolProperty("PlanarFigureInitializedWindow", PlanarFigureInitializedWindow, RenderWindow1->GetRenderer()))
                    {
                        selectedRenderWindow = RenderWindow1;
                    }

                    if(!selectedRenderWindow && node->GetBoolProperty("PlanarFigureInitializedWindow", PlanarFigureInitializedWindow, RenderWindow2->GetRenderer()))
                    {
                        selectedRenderWindow = RenderWindow2;
                    }

                    if(!selectedRenderWindow && node->GetBoolProperty("PlanarFigureInitializedWindow", PlanarFigureInitializedWindow, RenderWindow3->GetRenderer()))
                    {
                        selectedRenderWindow = RenderWindow3;
                    }

                    if(!selectedRenderWindow && node->GetBoolProperty("PlanarFigureInitializedWindow", PlanarFigureInitializedWindow, RenderWindow4->GetRenderer()))
                    {
                        selectedRenderWindow = RenderWindow4;
                    }

                    const mitk::PlaneGeometry* _PlaneGeometry = _PlanarFigure->GetPlaneGeometry();

                    mitk::VnlVector normal = _PlaneGeometry->GetNormalVnl();

                    mitk::PlaneGeometry::ConstPointer _Plane1 = (mitk::PlaneGeometry::ConstPointer) RenderWindow1->GetRenderer()->GetCurrentWorldPlaneGeometry();
                    mitk::VnlVector normal1 = _Plane1->GetNormalVnl();

                    mitk::PlaneGeometry::ConstPointer _Plane2 = (mitk::PlaneGeometry::ConstPointer) RenderWindow2->GetRenderer()->GetCurrentWorldPlaneGeometry();
                    mitk::VnlVector normal2 = _Plane2->GetNormalVnl();

                    mitk::PlaneGeometry::ConstPointer _Plane3 = (mitk::PlaneGeometry::ConstPointer) RenderWindow3->GetRenderer()->GetCurrentWorldPlaneGeometry();
                    mitk::VnlVector normal3 = _Plane3->GetNormalVnl();

                    normal[0] = fabs(normal[0]);
                    normal[1] = fabs(normal[1]);
                    normal[2] = fabs(normal[2]);
                    normal1[0] = fabs(normal1[0]);
                    normal1[1] = fabs(normal1[1]);
                    normal1[2] = fabs(normal1[2]);
                    normal2[0] = fabs(normal2[0]);
                    normal2[1] = fabs(normal2[1]);
                    normal2[2] = fabs(normal2[2]);
                    normal3[0] = fabs(normal3[0]);
                    normal3[1] = fabs(normal3[1]);
                    normal3[2] = fabs(normal3[2]);

                    double ang1 = angle(normal, normal1);
                    double ang2 = angle(normal, normal2);
                    double ang3 = angle(normal, normal3);

                    if(ang1 < ang2 && ang1 < ang3)
                    {
                        selectedRenderWindow = RenderWindow1;
                    }
                    else
                    {
                        if(ang2 < ang3)
                        {
                            selectedRenderWindow = RenderWindow2;
                        }
                        else
                        {
                            selectedRenderWindow = RenderWindow3;
                        }
                    }

                    // re-orient view
                    if(selectedRenderWindow)
                    {
                        const mitk::Point3D &centerP = _PlaneGeometry->GetOrigin();
                        selectedRenderWindow->GetSliceNavigationController()->ReorientSlices(centerP, _PlaneGeometry->GetNormal());
                    }
                }
                break;
            }
            mitk::RenderingManager::GetInstance()->ForceImmediateUpdateAll();
        }

        auto MeasurementItem::setNodeProperties(mitk::DataNode::Pointer node) -> void
        {
            node->SetName("Measurement");
            node->SetProperty("measurement", mitk::BoolProperty::New(true));
        }

        void MeasurementItem::actionDrawLineTriggered()
        {
            this->setEnabled(false);

            mitk::PlanarLine::Pointer figure = mitk::PlanarLine::New();
            QString qString = QString("Line%1").arg(++d->m_LineCounter);
            this->addFigureToDataStorage(figure, qString);
        }

        void MeasurementItem::actionDrawPathTriggered()
        {
            this->setEnabled(false);

            mitk::PlanarPolygon::Pointer figure = mitk::PlanarPolygon::New();
            figure->ClosedOff();
            QString qString = QString("Path%1").arg(++d->m_PathCounter);
            mitk::DataNode::Pointer node = this->addFigureToDataStorage(figure, qString);
            node->SetProperty("planarfigure.isextendable", mitk::BoolProperty::New(true));
        }

        void MeasurementItem::actionDrawAngleTriggered()
        {
            this->setEnabled(false);
            mitk::PlanarAngle::Pointer figure = mitk::PlanarAngle::New();
            QString qString = QString("Angle%1").arg(++d->m_AngleCounter);
            this->addFigureToDataStorage(figure, qString);
        }

        void MeasurementItem::actionDrawFourPointAngleTriggered()
        {
            this->setEnabled(false);

            mitk::PlanarFourPointAngle::Pointer figure = mitk::PlanarFourPointAngle::New();
            QString qString = QString("Four Point Angle%1").arg(++d->m_FourPointAngleCounter);
            this->addFigureToDataStorage(figure, qString);
        }

        void MeasurementItem::actionDrawCircleTriggered()
        {

            this->setEnabled(false);

            mitk::PlanarCircle::Pointer figure = mitk::PlanarCircle::New();
            QString qString = QString("Circle%1").arg(++d->m_CircleCounter);
            this->addFigureToDataStorage(figure, qString);
        }

        void MeasurementItem::actionDrawEllipseTriggered()
        {
            this->setEnabled(false);

            mitk::PlanarEllipse::Pointer figure = mitk::PlanarEllipse::New();
            QString qString = QString("Ellipse%1").arg(++d->m_EllipseCounter);
            this->addFigureToDataStorage(figure, qString);
        }

        void MeasurementItem::actionDrawDoubleEllipseTriggered()
        {
            this->setEnabled(false);

            mitk::PlanarDoubleEllipse::Pointer figure = mitk::PlanarDoubleEllipse::New();
            QString qString = QString("DoubleEllipse%1").arg(++d->m_DoubleEllipseCounter);
            this->addFigureToDataStorage(figure, qString);
        }

        void MeasurementItem::actionDrawBezierCurveTriggered()
        {
            this->setEnabled(false);

            mitk::PlanarBezierCurve::Pointer figure = mitk::PlanarBezierCurve::New();
            QString qString = QString("BezierCurve%1").arg(++d->m_BezierCurveCounter);
            this->addFigureToDataStorage(figure, qString);
        }

        void MeasurementItem::actionDrawSubdivisionPolygonTriggered()
        {
            this->setEnabled(false);

            mitk::PlanarSubdivisionPolygon::Pointer figure = mitk::PlanarSubdivisionPolygon::New();
            QString qString = QString("SubdivisionPolygon%1").arg(++d->m_SubdivisionPolygonCounter);
            this->addFigureToDataStorage(figure, qString);
        }

        void MeasurementItem::actionDrawRectangleTriggered()
        {
            this->setEnabled(false);

            mitk::PlanarRectangle::Pointer figure = mitk::PlanarRectangle::New();
            QString qString = QString("Rectangle%1").arg(++d->m_RectangleCounter);
            this->addFigureToDataStorage(figure, qString);
        }

        void MeasurementItem::actionDrawPolygonTriggered()
        {
            this->setEnabled(false);

            mitk::PlanarPolygon::Pointer figure = mitk::PlanarPolygon::New();
            figure->ClosedOn();
            QString qString = QString("Polygon%1").arg(++d->m_PolygonCounter);
            mitk::DataNode::Pointer node = this->addFigureToDataStorage(figure, qString);
            node->SetProperty("planarfigure.isextendable", mitk::BoolProperty::New(true));
        }

        auto MeasurementItem::addFigureToDataStorage(mitk::PlanarFigure* figure, const QString &name) -> mitk::DataNode::Pointer
        {
            mitk::DataNode::Pointer newNode = d->m_SelectedImageNode;
            newNode->SetName(name.toStdString());
            newNode->SetData(figure);
            newNode->SetProperty("measurement", mitk::BoolProperty::New(true));
            this->initNode(newNode);

            for(int i = 0; i < d->m_CurrentSelection.size(); ++i)
            {
                d->m_CurrentSelection.at(i)->SetSelected(false);
            }
            d->m_CurrentSelection.clear();
            d->m_CurrentSelection.push_back(newNode);

            this->updateMeasurementText();
            this->disableCrosshairNavigation();

            d->m_UnintializedPlanarFigure = true;
            this->setEnabled(false);
            return newNode;
        }

        auto MeasurementItem::updateMeasurementText() -> void
        {
            QString infoText;
            QString plainInfoText;
            int j = 1;
            mitk::PlanarFigure* _PlanarFigure = 0;
            mitk::PlanarAngle* planarAngle = 0;
            mitk::PlanarFourPointAngle* planarFourPointAngle = 0;
            mitk::DataNode::Pointer node = 0;

            for(int i = 0; i < d->m_CurrentSelection.size(); ++i, ++j)
            {
                plainInfoText.clear();
                node = d->m_CurrentSelection.at(i);
                _PlanarFigure = dynamic_cast<mitk::PlanarFigure*> (node->GetData());

                if(!_PlanarFigure)
                {
                    continue;
                }

                if(j > 1)
                {
                    infoText.append("<br />");
                }

                infoText.append(QString("<b>%1</b><hr />").arg(QString::fromStdString(node->GetName())));
                plainInfoText.append(QString("%1").arg(QString::fromStdString(node->GetName())));

                planarAngle = dynamic_cast<mitk::PlanarAngle*> (_PlanarFigure);
                if(!planarAngle)
                {
                    planarFourPointAngle = dynamic_cast<mitk::PlanarFourPointAngle*> (_PlanarFigure);
                }

                double featureQuantity = 0.0;
                for(unsigned int k = 0; k < _PlanarFigure->GetNumberOfFeatures(); ++k)
                {
                    if(!_PlanarFigure->IsFeatureActive(k))
                    {
                        continue;
                    }

                    featureQuantity = _PlanarFigure->GetQuantity(k);
                    if((planarAngle && k == planarAngle->FEATURE_ID_ANGLE) || (planarFourPointAngle && k == planarFourPointAngle->FEATURE_ID_ANGLE))
                    {
                        featureQuantity = featureQuantity * 180 / vnl_math::pi;
                    }

                    infoText.append(QString("<i>%1</i>: %2 %3").arg(QString(_PlanarFigure->GetFeatureName(k))).arg(featureQuantity, 0, 'f', 2).arg(QString(_PlanarFigure->GetFeatureUnit(k))));
                    plainInfoText.append(QString("\n%1: %2 %3").arg(QString(_PlanarFigure->GetFeatureName(k))).arg(featureQuantity, 0, 'f', 2).arg(QString(_PlanarFigure->GetFeatureUnit(k))));

                    if(k + 1 != _PlanarFigure->GetNumberOfFeatures())
                    {
                        infoText.append("<br />");
                    }
                }

                if(j != d->m_CurrentSelection.size())
                {
                    infoText.append("<br />");
                }
            }
            this->setText(infoText);
        }

        auto MeasurementItem::addAllInteractors() -> void
        {
            mitk::DataStorage::SetOfObjects::ConstPointer planarFigures = this->getAllPlanarFigures();

            for(mitk::DataStorage::SetOfObjects::ConstIterator it = planarFigures->Begin(); it != planarFigures->End();
                it++)
            {
                this->initNode(it.Value());
            }
        }

        auto MeasurementItem::removeAllInteractors() -> void
        {
            mitk::DataStorage::SetOfObjects::ConstPointer planarFigures = this->getAllPlanarFigures();

            for(mitk::DataStorage::SetOfObjects::ConstIterator it = planarFigures->Begin(); it != planarFigures->End();
                it++)
            {
                this->nodeRemoved(it.Value());
            }
        }

        auto MeasurementItem::detectTopMostVisibleImage() -> mitk::DataNode::Pointer
        {
            mitk::TNodePredicateDataType<mitk::Image>::Pointer isImage = mitk::TNodePredicateDataType<mitk::Image>::New();
            mitk::NodePredicateProperty::Pointer isBinary = mitk::NodePredicateProperty::New("binary", mitk::BoolProperty::New(true));
            mitk::NodePredicateNot::Pointer isNotBinary = mitk::NodePredicateNot::New(isBinary);
            mitk::NodePredicateAnd::Pointer isNormalImage = mitk::NodePredicateAnd::New(isImage, isNotBinary);

            mitk::DataStorage::SetOfObjects::ConstPointer Images = storage->GetSubset(isNormalImage);

            mitk::DataNode::Pointer currentNode;
            int maxLayer = itk::NumericTraits<int>::min();

            for(mitk::DataStorage::SetOfObjects::ConstIterator sofIt = Images->Begin(); sofIt != Images->End(); ++sofIt)
            {
                mitk::DataNode::Pointer node = sofIt->Value();
                if(node.IsNull())
                {
                    continue;
                }

                if(!node->IsVisible(NULL))
                {
                    continue;
                }

                if(node->GetProperty("helper object"))
                {
                    continue;
                }

                int layer = 0;
                node->GetIntProperty("layer", layer);
                if(layer < maxLayer)
                {
                    continue;
                }
                else
                {
                    maxLayer = layer;
                    currentNode = node;
                }
            }

            return currentNode;
        }

        auto MeasurementItem::enableCrosshairNavigation() -> void
        {
            for(std::map<us::ServiceReferenceU, mitk::EventConfig>::iterator it = m_DisplayInteractorConfigs.begin();
                it != m_DisplayInteractorConfigs.end(); ++it)
            {
                if(it->first)
                {
                    mitk::DisplayInteractor* displayInteractor = static_cast<mitk::DisplayInteractor*>(us::GetModuleContext()->GetService<mitk::InteractionEventObserver>(it->first));
                    if(displayInteractor != NULL)
                    {
                        // here the regular configuration is loaded again
                        displayInteractor->SetEventConfig(it->second);
                        MITK_INFO << "restore config";
                    }
                }
            }
            m_DisplayInteractorConfigs.clear();
            d->m_ScrollEnabled = true;

            StdMultiItem::instance->togglePlanes();
            this->updateMeasurementText();
        }

        auto MeasurementItem::disableCrosshairNavigation() -> void
        {
            if(!d->m_ScrollEnabled)
            {
                return;
            }

            m_DisplayInteractorConfigs.clear();
            std::vector<us::ServiceReference<mitk::InteractionEventObserver> > listEventObserver = us::GetModuleContext()->GetServiceReferences<mitk::InteractionEventObserver>();
            for(std::vector<us::ServiceReference<mitk::InteractionEventObserver> >::iterator it = listEventObserver.begin();
                it != listEventObserver.end(); ++it)
            {
                mitk::DisplayInteractor* displayInteractor = dynamic_cast<mitk::DisplayInteractor*>(us::GetModuleContext()->GetService<mitk::InteractionEventObserver>(*it));
                if(displayInteractor != NULL)
                {
                    m_DisplayInteractorConfigs.insert(std::make_pair(*it, displayInteractor->GetEventConfig()));
                    displayInteractor->SetEventConfig("DisplayConfigMITKLimited.xml");
                }
            }
            StdMultiItem::instance->togglePlanes();
            d->m_ScrollEnabled = false;
        }

        auto MeasurementItem::getAllPlanarFigures() -> mitk::DataStorage::SetOfObjects::ConstPointer const
        {
            mitk::TNodePredicateDataType<mitk::PlanarFigure>::Pointer isPlanarFigure = mitk::TNodePredicateDataType<mitk::PlanarFigure>::New();
            return storage->GetSubset(isPlanarFigure);
        }

        auto MeasurementItem::setText(QString text) -> void
        {
            this->m_Text = text;
            emit this->textChanged();
        }

        auto MeasurementItem::getText() -> QString
        {
            return this->m_Text;
        }

        auto MeasurementItem::setInfoText(QString text) -> void
        {
            this->m_InfoText = text;
            emit this->infoTextChanged();
        }

        auto MeasurementItem::getInfoText() -> QString
        {
            return this->m_InfoText;
        }
    }
}
