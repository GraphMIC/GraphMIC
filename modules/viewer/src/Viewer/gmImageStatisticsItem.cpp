#include "gmImageStatisticsItem.hpp"
#include "gmRenderWindowItem.hpp"
#include "gmStdMultiItem.hpp"
#include "gmDatamanager.hpp"
#include "gmPropertyController.hpp"
#include <mitkNodePredicateDataType.h>
#include <mitkNodePredicateOr.h>
#include <mitkPlanarFigureInteractor.h>
#include <itksys/SystemTools.hxx>
#include <QtConcurrent>

namespace gm
{
    namespace ViewItem
    {
        ImageStatisticsItem* ImageStatisticsItem::instance = nullptr;

        ImageStatisticsItem::ImageStatisticsItem(QObject* /*parent*/, const char* /*name*/)
        :m_timeStepperAdapter(nullptr ),
        m_histogramInfo(""),
        m_selectedImage(nullptr),
        m_selectedImageMask(nullptr),
        m_selectedPlanarFigure(nullptr),
        m_imageObserverTag(-1),
        m_imageMaskObserverTag(-1),
        m_planarFigureObserverTag(-1),
        m_timeObserverTag(-1),
        m_defaultBinSize(true),
        m_currentStatisticsValid(false),
        m_statisticsUpdatePending(false),
        m_dataNodeSelectionChanged(false),
        m_visible(false),
        m_calculationThread(new ImageStatisticsCalculation)
        {
            if(instance)
            {
                throw("Instance already existing");
            }
            instance = this;
            setEnabled(false);
            this->m_futureWatcher = new QFutureWatcher<void>();

            connect(this->m_futureWatcher, &QFutureWatcher<void>::finished, this, &ImageStatisticsItem::onThreadedStatisticsCalculationEnds);
            connect(this, &ImageStatisticsItem::statisticsUpdate, this, &ImageStatisticsItem::requestStatisticsUpdate, Qt::QueuedConnection);
            connect(DataManager::instance, &DataManager::notifySelection, this, &ImageStatisticsItem::receive);
            connect(this, &ImageStatisticsItem::setStatus, PropertyController::instance, &PropertyController::setStatistics);
        }

        ImageStatisticsItem::~ImageStatisticsItem()
        {
            if ( m_selectedImage != NULL )
                m_selectedImage->RemoveObserver(m_imageObserverTag);
            if ( m_selectedImageMask != NULL )
                m_selectedImageMask->RemoveObserver(m_imageMaskObserverTag);
            if ( m_selectedPlanarFigure != NULL )
                m_selectedPlanarFigure->RemoveObserver(m_planarFigureObserverTag);

            while(this->m_futureWatcher->isRunning())
            {
                itksys::SystemTools::Delay(100);
            }
            delete this->m_calculationThread;
        }

        void ImageStatisticsItem::receive(mitk::DataNode::Pointer node)
        {

            if(!node)
            {
                setEnabled(false);
                return;
            }

            bool isImage = false;
            node->GetBoolProperty("image", isImage);

            if(isImage)
            {
                this->m_node = node;
                this->computeStatistics();
                setEnabled(true);
                emit this->setStatus(true);
            }
            else
            {
                setEnabled(false);
                emit this->setStatus(false);
            }
        }

        auto ImageStatisticsItem::setIgnoreZeroValues(bool status) -> void
        {
            this->m_ignoreZeroValues = status;
        }

        auto ImageStatisticsItem::isIgnoreZeroValues() -> bool
        {
            return this->m_ignoreZeroValues;
        }

        auto ImageStatisticsItem::setHistogramInfo(QString info) -> void
        {
            this->m_histogramInfo = info;
            emit this->histogramInfoChanged();
        }

        auto ImageStatisticsItem::getHistogramInfo() -> QString
        {
            return this->m_histogramInfo;
        }

        auto ImageStatisticsItem::setHistogramItem(HistogramItem *item) -> void
        {
            this->m_histogramItem = item;
        }

        auto ImageStatisticsItem::getHistogramItem() -> HistogramItem*
        {
            return this->m_histogramItem;
        }

        auto ImageStatisticsItem::setBinSize(int size) -> void
        {
            if(this->m_binSize == size)
                return;

            this->m_binSize = size;

            if(this->m_calculationThread)
            {
                this->requestStatisticsUpdate();
            }


            emit this->binSizeChanged();
        }

        auto ImageStatisticsItem::getBinSize() -> int
        {
            return this->m_binSize;
        }

        auto ImageStatisticsItem::setSpinBoxStatus(bool status) -> void
        {
            this->m_spinBoxStatus = status;
            emit this->spinBoxStatusChanged();
        }

        auto ImageStatisticsItem::getSpinBoxStatus() -> bool
        {
            return this->m_spinBoxStatus;
        }

        auto ImageStatisticsItem::setDefaultBinSize(bool status) -> void
        {
            this->m_defaultBinSize = status;

            if (m_calculationThread !=NULL)
            {
                this->setBinSize(m_calculationThread->getHistogramBinSize());
                this->setSpinBoxStatus(!this->m_defaultBinSize);
            }

            emit this->defaultBinSizeChanged();
        }

        auto ImageStatisticsItem::isDefaultBinSize() -> bool
        {
            return this->m_defaultBinSize;
        }

        void ImageStatisticsItem::computeStatistics()
        {
            QList<mitk::DataNode::Pointer> selectedNodes;
            selectedNodes.push_back(this->m_node);

            this->selectionChanged(selectedNodes);
        }

        void ImageStatisticsItem::selectionChanged(const QList<mitk::DataNode::Pointer> &selectedNodes)
        {
            if( this->m_statisticsUpdatePending)
            {
                this->m_dataNodeSelectionChanged = true;
                return;
            }

            if (selectedNodes.size() == this->m_selectedDataNodes.size())
            {
                int i = 0;
                for (; i < selectedNodes.size(); ++i)
                {
                    if (selectedNodes.at(i) != this->m_selectedDataNodes.at(i))
                    {
                        break;
                    }
                }
                if (i == selectedNodes.size()) return;
            }

            this->reinitData();
            if (selectedNodes.isEmpty())
            {
                this->m_histogramItem->clearHistogram();
                this->setEnabled(false);
            }
            else
            {
                this->setEnabled(true);
            }

            if(selectedNodes.size() == 1 || selectedNodes.size() == 2)
            {
                bool isBinary = false;
                selectedNodes.value(0)->GetBoolProperty("binary",isBinary);
                mitk::NodePredicateDataType::Pointer isLabelSet = mitk::NodePredicateDataType::New("LabelSetImage");
                isBinary |= isLabelSet->CheckNode(selectedNodes.value(0));

                if(isBinary)
                {

                    this->m_histogramItem->clearHistogram();
                    this->setEnabled(false);
                }

                for (int i= 0; i< selectedNodes.size(); ++i)
                {
                    this->m_selectedDataNodes.push_back((mitk::DataNode* const &) selectedNodes.at(i));
                }

                this->m_dataNodeSelectionChanged = false;
                emit statisticsUpdate();
            }
            else
            {
                this->m_dataNodeSelectionChanged = false;
            }
        }

        void ImageStatisticsItem::reinitData()
        {

            while(this->m_futureWatcher->isRunning())
            {
                itksys::SystemTools::Delay(100);
            }

            if(this->m_selectedImage != NULL)
            {
                this->m_selectedImage->RemoveObserver( this->m_imageObserverTag);
                this->m_selectedImage = NULL;
            }
            if(this->m_selectedImageMask != NULL)
            {
                this->m_selectedImageMask->RemoveObserver( this->m_imageMaskObserverTag);
                this->m_selectedImageMask = NULL;
            }
            if(this->m_selectedPlanarFigure != NULL)
            {
                this->m_selectedPlanarFigure->RemoveObserver( this->m_planarFigureObserverTag);
                this->m_selectedPlanarFigure = NULL;
            }
            this->m_selectedDataNodes.clear();
            this->m_statisticsUpdatePending = false;

            this->invalidateStatisticsTableView();
        }

        void ImageStatisticsItem::onThreadedStatisticsCalculationEnds()
        {
            this->writeStatisticsToGUI();
        }

        void ImageStatisticsItem::updateStatistics()
        {
            m_worldMinList.clear();
            m_worldMaxList.clear();

            mitk::NodePredicateDataType::Pointer isImage = mitk::NodePredicateDataType::New("Image");
            mitk::NodePredicateDataType::Pointer isLabelSet = mitk::NodePredicateDataType::New("LabelSetImage");
            mitk::NodePredicateOr::Pointer imagePredicate = mitk::NodePredicateOr::New(isImage, isLabelSet);

            std::string maskName = std::string();
            std::string maskType = std::string();
            std::string featureImageName = std::string();
            unsigned int maskDimension = 0;

            ITKCommandType::Pointer changeListener = ITKCommandType::New();
            changeListener->SetCallbackFunction(this, &ImageStatisticsItem::selectedDataModified);

            mitk::DataNode::Pointer planarFigureNode;
            for(int i= 0 ; i < this->m_selectedDataNodes.size(); ++i)
            {
                mitk::PlanarFigure::Pointer planarFig = dynamic_cast<mitk::PlanarFigure*>(this->m_selectedDataNodes.at(i)->GetData());
                if( imagePredicate->CheckNode(this->m_selectedDataNodes.at(i)) )
                {
                    bool isMask = false;
                    this->m_selectedDataNodes.at(i)->GetPropertyValue("binary", isMask);
                    isMask |= isLabelSet->CheckNode(this->m_selectedDataNodes.at(i));

                    if( this->m_selectedImageMask == NULL && isMask)
                    {
                        this->m_selectedImageMask = dynamic_cast<mitk::Image*>(this->m_selectedDataNodes.at(i)->GetData());
                        this->m_imageMaskObserverTag = this->m_selectedImageMask->AddObserver(itk::ModifiedEvent(), changeListener);

                        maskName = this->m_selectedDataNodes.at(i)->GetName();
                        maskType = m_selectedImageMask->GetNameOfClass();
                        maskDimension = 3;
                    }
                    else if( !isMask )
                    {
                        if(this->m_selectedImage == NULL)
                        {
                            this->m_selectedImage = static_cast<mitk::Image*>(this->m_selectedDataNodes.at(i)->GetData());
                            this->m_imageObserverTag = this->m_selectedImage->AddObserver(itk::ModifiedEvent(), changeListener);
                        }
                        featureImageName = this->m_selectedDataNodes.at(i)->GetName();
                    }
                }
                else if (planarFig.IsNotNull())
                {
                    if(this->m_selectedPlanarFigure == NULL)
                    {
                        this->m_selectedPlanarFigure = planarFig;
                        this->m_planarFigureObserverTag =
                        this->m_selectedPlanarFigure->AddObserver(mitk::EndInteractionPlanarFigureEvent(), changeListener);
                        maskName = this->m_selectedDataNodes.at(i)->GetName();
                        maskType = this->m_selectedPlanarFigure->GetNameOfClass();
                        maskDimension = 2;
                        planarFigureNode = m_selectedDataNodes.at(i);
                    }
                }
                else
                {
                    std::stringstream message;
                    message << "<font color='red'>" << "Invalid data node type!" << "</font>";
                }
            }

            if(maskName == "")
            {
                maskName = "None";
                maskType = "";
                maskDimension = 0;
            }

            if(featureImageName == "")
            {
                featureImageName = "None";
            }

            if (m_selectedPlanarFigure != NULL && m_selectedImage == NULL)
            {
                mitk::DataStorage::SetOfObjects::ConstPointer parentSet = m_dataStorage->GetSources(planarFigureNode);
                for (int i=0; i<parentSet->Size(); i++)
                {
                    mitk::DataNode::Pointer node = parentSet->ElementAt(i);
                    if( imagePredicate->CheckNode(node) )
                    {
                        bool isMask = false;
                        node->GetPropertyValue("binary", isMask);
                        isMask |= isLabelSet->CheckNode(node);

                        if( !isMask )
                        {
                            if(this->m_selectedImage == NULL)
                            {
                                this->m_selectedImage = static_cast<mitk::Image*>(node->GetData());
                                this->m_imageObserverTag = this->m_selectedImage->AddObserver(itk::ModifiedEvent(), changeListener);
                            }
                        }
                    }
                }
            }

            unsigned int timeStep = 0;

            if ( m_selectedImage != NULL && m_selectedImage->IsInitialized())
            {
                // Check if a the selected image is a multi-channel image. If yes, statistics
                // cannot be calculated currently.
                if ( m_selectedImage->GetPixelType().GetNumberOfComponents() > 1 )
                {

                    this->invalidateStatisticsTableView();
                    this->m_histogramItem->clearHistogram();
                    //this->m_statisticsUpdatePending = false;

                    return;
                }

                std::stringstream maskLabel;
                maskLabel << maskName;
                if ( maskDimension > 0 )
                {
                    maskLabel << "  [" << maskDimension << "D " << maskType << "]";
                }

                if(m_selectedImage->GetDimension() <= 3 && timeStep > m_selectedImage->GetDimension(3)-1)
                {
                    timeStep = m_selectedImage->GetDimension(3)-1;
                }

                if (m_selectedImageMask != NULL)
                {
                    unsigned int maskTimeStep = timeStep;

                    if (maskTimeStep >= m_selectedImageMask->GetTimeSteps())
                    {
                        maskTimeStep = m_selectedImageMask->GetTimeSteps() - 1;
                    }
                }

                this->m_calculationThread->setIgnoreZeroValueVoxel(this->m_ignoreZeroValues);
                this->m_calculationThread->initialize(m_selectedImage, m_selectedImageMask, m_selectedPlanarFigure);
                this->m_calculationThread->setTimeStep(timeStep);
                this->m_calculationThread->setUseDefaultBinSize(this->m_defaultBinSize);

                if(!this->m_defaultBinSize)
                {
                    this->m_calculationThread->setHistogramBinSize(this->m_binSize);
                }

                try
                {
                    this->m_calculationThread->setUseDefaultBinSize(this->m_defaultBinSize);
                    QFuture<void> future = QtConcurrent::run(this->m_calculationThread,&ImageStatisticsCalculation::run);
                    this->m_futureWatcher->setFuture(future);

                }
                catch ( const mitk::Exception& e)
                {
                    this->m_statisticsUpdatePending = false;
                }
                catch ( const std::runtime_error &e )
                {
                    this->m_statisticsUpdatePending = false;
                }
                catch ( const std::exception &e )
                {
                    this->m_statisticsUpdatePending = false;
                }
            }
            else
            {
                this->m_statisticsUpdatePending = false;
            }
        }

        void ImageStatisticsItem::selectedDataModified()
        {
            if( !m_statisticsUpdatePending)
            {
                emit statisticsUpdate();
            }
        }

        void ImageStatisticsItem::nodeRemoved(const mitk::DataNode* node)
        {

            while(this->m_futureWatcher->isRunning())
            {
                itksys::SystemTools::Delay(100);
            }

            if (node->GetData() == m_selectedImage)
            {
                m_selectedImage = NULL;
            }
        }

        auto ImageStatisticsItem::requestStatisticsUpdate() -> void
        {

            while(this->m_futureWatcher->isRunning())
            {
                itksys::SystemTools::Delay(100);
            }

            if ( !m_statisticsUpdatePending)
            {
                if(this->m_dataNodeSelectionChanged)
                {
                    //this->SelectionChanged(this->GetCurrentSelection());
                }
                else
                {
                    this->m_statisticsUpdatePending = true;
                    this->updateStatistics();
                }
            }
        }

        auto ImageStatisticsItem::writeStatisticsToGUI() -> void
        {

            if(m_futureWatcher && m_futureWatcher->isRunning())
            {
                return;
            }

            if(m_dataNodeSelectionChanged)
            {
                this->m_statisticsUpdatePending = false;
                this->requestStatisticsUpdate();
                return;
            }

            if (this->m_calculationThread->getStatisticsUpdateSuccessFlag())
            {
                if (this->m_calculationThread->getStatisticsChangedFlag() )
                {
                    m_currentStatisticsValid = true;
                }

                this->setBinSize(this->m_calculationThread->getHistogramBinSize() );
                this->m_histogramItem->computeHistogram(this->m_calculationThread->getTimeStepHistogram(this->m_calculationThread->getTimeStep()).GetPointer(), this->m_calculationThread->getStatisticsData()[0].GetMax());

                this->fillStatisticsTableView(this->m_calculationThread->getStatisticsData(), this->m_calculationThread->getStatisticsImage());
            }
            else
            {
                this->invalidateStatisticsTableView();
                this->m_histogramItem->clearHistogram();

                m_currentStatisticsValid = false;

                if ( m_selectedPlanarFigure != NULL )
                {
                    bool outOfBounds = false;
                    if ( m_selectedPlanarFigure->IsClosed() && m_selectedImageMask == NULL)
                    {
                        outOfBounds = true;
                    }

                    const mitk::PlaneGeometry *planarFigurePlaneGeometry = m_selectedPlanarFigure->GetPlaneGeometry();
                    if ( planarFigurePlaneGeometry == NULL || outOfBounds)
                    {
                        this->invalidateStatisticsTableView();
                        this->m_histogramItem->clearHistogram();
                        m_currentStatisticsValid = false;
                        this->m_statisticsUpdatePending = false;
                        return;
                    }
                    this->m_histogramItem->setImage(this->m_calculationThread->getStatisticsImage());
                    //this->fillLinearProfileStatisticsTableView(this->m_calculationThread->GetStatisticsImage());
                }
            }
            this->m_statisticsUpdatePending = false;

        }

        void ImageStatisticsItem::fillStatisticsTableView(const std::vector<mitk::ImageStatisticsCalculator::Statistics> &s, const mitk::Image* image)
        {
            int decimals = 2;

            mitk::PixelType doublePix = mitk::MakeScalarPixelType< double >();
            mitk::PixelType floatPix = mitk::MakeScalarPixelType< float >();

            if (image->GetPixelType()==doublePix || image->GetPixelType()==floatPix)
            {
                decimals = 5;
            }

            for (unsigned int t = 0; t < image->GetTimeSteps(); t++)
            {
                if (s[t].GetMaxIndex().size()==3)
                {
                    mitk::Point3D index, max, min;
                    index[0] = s[t].GetMaxIndex()[0];
                    index[1] = s[t].GetMaxIndex()[1];
                    index[2] = s[t].GetMaxIndex()[2];
                    m_selectedImage->GetGeometry()->IndexToWorld(index, max);
                    this->m_worldMaxList.push_back(max);
                    index[0] = s[t].GetMinIndex()[0];
                    index[1] = s[t].GetMinIndex()[1];
                    index[2] = s[t].GetMinIndex()[2];
                    m_selectedImage->GetGeometry()->IndexToWorld(index, min);
                    this->m_worldMinList.push_back(min);
                }
                this->invalidateStatisticsTableView();
                this->m_histogramInfo.append(QString("<b>Mean:</b> %1<br />").arg(s[t].GetMean(), 0, 'f', decimals));
                this->m_histogramInfo.append(QString("<b>Sigma:</b> %1<br />").arg(s[t].GetSigma(), 0, 'f', decimals));
                this->m_histogramInfo.append(QString("<b>RMS:</b> %1<br />").arg(s[t].GetRMS(), 0, 'f', decimals));

                QString max;
                max.append(QString("<b>Max:</b> %1 ").arg(s[t].GetMax(), 0, 'f', decimals));
                max += " (";
                for (int i=0; i<s[t].GetMaxIndex().size(); i++)
                {
                    max += QString::number(s[t].GetMaxIndex()[i]);
                    if (i<s[t].GetMaxIndex().size()-1)
                        max += ",";
                }
                max += ")<br />";

                QString min;
                min.append(QString("<b>Min:</b> %1 ").arg(s[t].GetMin(), 0, 'f', decimals));
                min += " (";
                for (int i=0; i<s[t].GetMinIndex().size(); i++)
                {
                    min += QString::number(s[t].GetMinIndex()[i]);
                    if (i<s[t].GetMinIndex().size()-1)
                        min += ",";
                }
                min += ")<br />";

                this->m_histogramInfo.append(max);
                this->m_histogramInfo.append(min);
                this->m_histogramInfo.append(QString("<b>N:</b> %1<br />").arg(s[t].GetN()));

                const mitk::BaseGeometry *geometry = image->GetGeometry();
                if ( geometry != NULL )
                {
                    const mitk::Vector3D &spacing = image->GetGeometry()->GetSpacing();
                    double volume = spacing[0] * spacing[1] * spacing[2] * (double) s[t].GetN();

                    this->m_histogramInfo.append(QString("<b>Volume:</b> %1<br />").arg(volume, 0, 'f', decimals));
                }
                else
                {
                    this->m_histogramInfo.append(QString("<b>Volume:</b> NA<br />"));
                }
            }

            emit this->histogramInfoChanged();
        }


        void ImageStatisticsItem::invalidateStatisticsTableView()
        {
            this->m_histogramInfo = "";
            emit this->histogramInfoChanged();
        }
    }
}