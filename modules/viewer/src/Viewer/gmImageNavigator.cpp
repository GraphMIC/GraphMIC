#include "gmImageNavigator.hpp"

#include <gmStdMultiItem.hpp>
#include <gmStepperAdapter.hpp>

namespace gm
{
    namespace ViewItem
    {
        ImageNavigator* ImageNavigator::instance = nullptr;
        
        ImageNavigator::ImageNavigator() : m_AxialStepper(0), m_SagittalStepper(0), m_FrontalStepper(0), m_TimeStepper(0)
        {
            if(instance)
                throw("Instance already existing");

            instance = this;
        }
        ImageNavigator::~ImageNavigator()
        {
        }
        
        auto ImageNavigator::setNavigatorAxial(SliderNavigatorItem *item) -> void
        {
            this->m_NavigatorAxial = item;
        }
        
        auto ImageNavigator::setNavigatorSagittal(SliderNavigatorItem *item) -> void
        {
            this->m_NavigatorSagittal = item;
        }
        
        auto ImageNavigator::setNavigatorCoronal(SliderNavigatorItem *item) -> void
        {
            this->m_NavigatorCoronal = item;
        }
        
        auto ImageNavigator::setNavigatorTime(SliderNavigatorItem *item) -> void
        {
            this->m_NavigatorTime = item;
        }
        
        auto ImageNavigator::getNavigatorAxial() -> SliderNavigatorItem*
        {
            return this->m_NavigatorAxial;
        }
        
        auto ImageNavigator::getNavigatorSagittal() -> SliderNavigatorItem*
        {
            return this->m_NavigatorSagittal;
        }
        
        auto ImageNavigator::getNavigatorCoronal() -> SliderNavigatorItem*
        {
            return this->m_NavigatorCoronal;
        }
        
        auto ImageNavigator::getNavigatorTime() -> SliderNavigatorItem*
        {
            return this->m_NavigatorTime;
        }
        
        auto ImageNavigator::setWorldCoordinateX(double coordinate) -> void
        {
            this->m_WorldCoordinateX = coordinate;
            this->onMillimetreCoordinateValueChanged();
        }
        
        auto ImageNavigator::setWorldCoordinateY(double coordinate) -> void
        {
            this->m_WorldCoordinateY = coordinate;
            this->onMillimetreCoordinateValueChanged();
        }
        
        auto ImageNavigator::setWorldCoordinateZ(double coordinate) -> void
        {
            this->m_WorldCoordinateZ = coordinate;
            this->onMillimetreCoordinateValueChanged();
        }
        
        auto ImageNavigator::setWorldCoordinateXMin(double coordinate) -> void
        {
            this->m_WorldCoordinateXMin = coordinate;
        }
        
        auto ImageNavigator::setWorldCoordinateYMin(double coordinate) -> void
        {
            this->m_WorldCoordinateYMin = coordinate;
        }
        
        auto ImageNavigator::setWorldCoordinateZMin(double coordinate) -> void
        {
            this->m_WorldCoordinateZMin = coordinate;
        }
        
        auto ImageNavigator::setWorldCoordinateXMax(double coordinate) -> void
        {
            this->m_WorldCoordinateXMax = coordinate;
        }
        
        auto ImageNavigator::setWorldCoordinateYMax(double coordinate) -> void
        {
            this->m_WorldCoordinateYMax = coordinate;
        }
        
        auto ImageNavigator::setWorldCoordinateZMax(double coordinate) -> void
        {
            this->m_WorldCoordinateZMax = coordinate;
        }
        
        auto ImageNavigator::getWorldCoordinateX() -> double
        {
            return this->m_WorldCoordinateX;
        }
        
        auto ImageNavigator::getWorldCoordinateY() -> double
        {
            return this->m_WorldCoordinateY;
        }
        
        auto ImageNavigator::getWorldCoordinateZ() -> double
        {
            return this->m_WorldCoordinateZ;
        }
        
        auto ImageNavigator::getWorldCoordinateXMin() -> double
        {
            return this->m_WorldCoordinateXMin;
        }
        
        auto ImageNavigator::getWorldCoordinateYMin() -> double
        {
            return this->m_WorldCoordinateYMin;
        }
        
        auto ImageNavigator::getWorldCoordinateZMin() -> double
        {
            return this->m_WorldCoordinateZMin;
        }
        
        auto ImageNavigator::getWorldCoordinateXMax() -> double
        {
            return this->m_WorldCoordinateXMax;
        }
        
        auto ImageNavigator::getWorldCoordinateYMax() -> double
        {
            return this->m_WorldCoordinateYMax;
        }
        
        auto ImageNavigator::getWorldCoordinateZMax() -> double
        {
            return this->m_WorldCoordinateZMax;
        }
        
        void ImageNavigator::initialize()
        {
            if(!StdMultiItem::instance)
                return;
            
            RenderWindowItem* renderWindow = StdMultiItem::instance->getViewerAxial();
            
            if (renderWindow)
            {
                if (m_AxialStepper) m_AxialStepper->deleteLater();
                m_AxialStepper = new StepperAdapter(this->m_NavigatorAxial,
                                                         renderWindow->GetSliceNavigationController()->GetSlice(),
                                                         "sliceNavigatorAxialFromSimpleExample");
                
                connect(m_AxialStepper, SIGNAL(Refetch()), this, SLOT(onRefetch()));
            }
            else
            {
                this->m_NavigatorAxial->setEnabled(false);
            }
            
            renderWindow = StdMultiItem::instance->getViewerSagittal();
            if (renderWindow)
            {
                if (m_SagittalStepper) m_SagittalStepper->deleteLater();
                m_SagittalStepper = new StepperAdapter(this->m_NavigatorSagittal,
                                                            renderWindow->GetSliceNavigationController()->GetSlice(),
                                                            "sliceNavigatorSagittalFromSimpleExample");
                connect(m_SagittalStepper, SIGNAL(Refetch()), this, SLOT(onRefetch()));
            }
            else
            {
                this->m_NavigatorSagittal->setEnabled(false);
            }
            
            renderWindow = StdMultiItem::instance->getViewerCoronal();
            if (renderWindow)
            {
                if (m_FrontalStepper) m_FrontalStepper->deleteLater();
                m_FrontalStepper = new StepperAdapter(this->m_NavigatorCoronal,
                                                           renderWindow->GetSliceNavigationController()->GetSlice(),
                                                           "sliceNavigatorFrontalFromSimpleExample");
                connect(m_FrontalStepper, SIGNAL(Refetch()), this, SLOT(onRefetch()));
            }
            else
            {
                this->m_NavigatorCoronal->setEnabled(false);
            }
            
            mitk::SliceNavigationController* timeController = mitk::RenderingManager::GetInstance()->GetTimeNavigationController();
            if (timeController)
            {
                if (m_TimeStepper) m_TimeStepper->deleteLater();
                m_TimeStepper = new StepperAdapter(this->m_NavigatorTime,
                                                        timeController->GetTime(),
                                                        "sliceNavigatorTimeFromSimpleExample");
            }
            else
            {
                this->m_NavigatorTime->setEnabled(false);
            }
        }
        
        auto ImageNavigator::getClosestAxisIndex(mitk::Vector3D normal) -> int
        {
            double absCosThetaWithAxis[3];
            
            for (int i = 0; i < 3; i++)
            {
                absCosThetaWithAxis[i] = fabs(normal[i]);
            }
            int largestIndex = 0;
            double largestValue = absCosThetaWithAxis[0];
            for (int i = 1; i < 3; i++)
            {
                if (absCosThetaWithAxis[i] > largestValue)
                {
                    largestValue = absCosThetaWithAxis[i];
                    largestIndex = i;
                }
            }
            return largestIndex;
        }
        
        auto ImageNavigator::setStepSizes() -> void
        {
            this->setStepSize(0);
            this->setStepSize(1);
            this->setStepSize(2);
        }

        auto ImageNavigator::setStepSize(int /*axis*/, double /*stepSize*/) -> void
        {

        }
        
        auto ImageNavigator::setStepSize(int axis) -> void
        {
            mitk::BaseGeometry::ConstPointer geometry = (mitk::BaseGeometry::ConstPointer) StdMultiItem::instance->getViewerAxial()->GetSliceNavigationController()->GetInputWorldGeometry3D();
            
            if (geometry.IsNotNull())
            {
                mitk::Point3D crossPositionInIndexCoordinates;
                mitk::Point3D crossPositionInIndexCoordinatesPlus1;
                mitk::Point3D crossPositionInMillimetresPlus1;
                mitk::Vector3D transformedAxisDirection;
                
                mitk::Point3D crossPositionInMillimetres = StdMultiItem::instance->getCrossPosition();
                geometry->WorldToIndex(crossPositionInMillimetres, crossPositionInIndexCoordinates);
                
                crossPositionInIndexCoordinatesPlus1 = crossPositionInIndexCoordinates;
                crossPositionInIndexCoordinatesPlus1[axis] += 1;
                
                geometry->IndexToWorld(crossPositionInIndexCoordinatesPlus1, crossPositionInMillimetresPlus1);
                
                transformedAxisDirection = crossPositionInMillimetresPlus1 - crossPositionInMillimetres;
                
                int closestAxisInMillimetreSpace = this->getClosestAxisIndex(transformedAxisDirection);
                double stepSize = transformedAxisDirection.GetNorm();
                this->setStepSize(closestAxisInMillimetreSpace, stepSize);
            }
        }
        
        auto ImageNavigator::onMillimetreCoordinateValueChanged() -> void
        {
            if(!StdMultiItem::instance)
                return;

            mitk::TimeGeometry::ConstPointer geometry = (mitk::TimeGeometry::ConstPointer) StdMultiItem::instance->getViewerAxial()->GetSliceNavigationController()->GetInputWorldTimeGeometry();
            
            if (geometry.IsNotNull())
            {
                mitk::Point3D positionInWorldCoordinates;
                positionInWorldCoordinates[0] = this->m_WorldCoordinateX;
                positionInWorldCoordinates[1] = this->m_WorldCoordinateY;
                positionInWorldCoordinates[2] = this->m_WorldCoordinateZ;
                
                StdMultiItem::instance->moveCrossToPosition(positionInWorldCoordinates);
            }
        }
        
        auto ImageNavigator::onRefetch() -> void
        {
            if(!StdMultiItem::instance)
                return;

            mitk::BaseGeometry::ConstPointer geometry = (mitk::BaseGeometry::ConstPointer) StdMultiItem::instance->getViewerAxial()->GetSliceNavigationController()->GetInputWorldGeometry3D();
            mitk::TimeGeometry::ConstPointer timeGeometry = (mitk::TimeGeometry::ConstPointer) StdMultiItem::instance->getViewerAxial()->GetSliceNavigationController()->GetInputWorldTimeGeometry();
            
            if (geometry.IsNull() && timeGeometry.IsNotNull())
            {
                mitk::TimeStepType timeStep = StdMultiItem::instance->getViewerAxial()->GetSliceNavigationController()->GetTime()->GetPos();
                geometry = timeGeometry->GetGeometryForTimeStep(timeStep);
            }
            
            if (geometry.IsNotNull())
            {
                mitk::BoundingBox::BoundsArrayType bounds = geometry->GetBounds();
                
                mitk::Point3D cornerPoint1InIndexCoordinates;
                cornerPoint1InIndexCoordinates[0] = bounds[0];
                cornerPoint1InIndexCoordinates[1] = bounds[2];
                cornerPoint1InIndexCoordinates[2] = bounds[4];
                
                mitk::Point3D cornerPoint2InIndexCoordinates;
                cornerPoint2InIndexCoordinates[0] = bounds[1];
                cornerPoint2InIndexCoordinates[1] = bounds[3];
                cornerPoint2InIndexCoordinates[2] = bounds[5];
                
                if (!geometry->GetImageGeometry())
                {
                    cornerPoint1InIndexCoordinates[0] += 0.5;
                    cornerPoint1InIndexCoordinates[1] += 0.5;
                    cornerPoint1InIndexCoordinates[2] += 0.5;
                    cornerPoint2InIndexCoordinates[0] -= 0.5;
                    cornerPoint2InIndexCoordinates[1] -= 0.5;
                    cornerPoint2InIndexCoordinates[2] -= 0.5;
                }
                
                mitk::Point3D crossPositionInWorldCoordinates = StdMultiItem::instance->getCrossPosition();
                
                mitk::Point3D cornerPoint1InWorldCoordinates;
                mitk::Point3D cornerPoint2InWorldCoordinates;
                
                geometry->IndexToWorld(cornerPoint1InIndexCoordinates, cornerPoint1InWorldCoordinates);
                geometry->IndexToWorld(cornerPoint2InIndexCoordinates, cornerPoint2InWorldCoordinates);
                
                this->m_WorldCoordinateXMin = std::min(cornerPoint1InWorldCoordinates[0], cornerPoint2InWorldCoordinates[0]);
                this->m_WorldCoordinateYMin = std::min(cornerPoint1InWorldCoordinates[1], cornerPoint2InWorldCoordinates[1]);
                this->m_WorldCoordinateZMin = std::min(cornerPoint1InWorldCoordinates[2], cornerPoint2InWorldCoordinates[2]);
                
                this->m_WorldCoordinateXMax = std::max(cornerPoint1InWorldCoordinates[0], cornerPoint2InWorldCoordinates[0]);
                this->m_WorldCoordinateYMax = std::max(cornerPoint1InWorldCoordinates[1], cornerPoint2InWorldCoordinates[1]);
                this->m_WorldCoordinateZMax = std::max(cornerPoint1InWorldCoordinates[2], cornerPoint2InWorldCoordinates[2]);
                
                this->m_WorldCoordinateX = crossPositionInWorldCoordinates[0];
                this->m_WorldCoordinateY = crossPositionInWorldCoordinates[1];
                this->m_WorldCoordinateZ = crossPositionInWorldCoordinates[2];
                
                emit this->sync();
            }
        }
    }
}