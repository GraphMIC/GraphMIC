#pragma once

#include "gmViewerExport.hpp"

#include "mitkStepper.h"

#include "itkObject.h"
#include "itkCommand.h"

#include <QObject>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT StepperAdapter: public QObject
        {
            Q_OBJECT
        public:
            StepperAdapter(QObject* navigator, mitk::Stepper* stepper, const char* name);
            virtual ~StepperAdapter();
            
            auto SetStepper(mitk::Stepper* stepper) -> void;
            
            class ItkEventListener: public itk::Command
            {
                public:
                mitkClassMacroItkParent(ItkEventListener, itk::Command);
                ItkEventListener(StepperAdapter* receiver) : m_Receiver(receiver)
                {
                    
                };
                virtual void Execute(itk::Object*, const itk::EventObject &) override
                {
                    emit m_Receiver->Refetch();
                };
                virtual void Execute(const itk::Object*, const itk::EventObject &) override
                {
                    emit m_Receiver->Refetch();
                };
                protected:
                StepperAdapter* m_Receiver;
            };
            
            signals:
                void Refetch();
                void SendStepper(mitk::Stepper*);
            
            protected:
                mitk::Stepper::Pointer m_Stepper;
                long m_ObserverTag;
                friend class StepperAdapter::ItkEventListener;
            
            ItkEventListener::Pointer m_ItkEventListener;
        };
    }
}

