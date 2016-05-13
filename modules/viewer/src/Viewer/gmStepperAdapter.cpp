#include "gmStepperAdapter.hpp"

namespace gm
{
    namespace ViewItem
    {
        StepperAdapter::StepperAdapter(QObject* navigator, mitk::Stepper* stepper, const char*) : QObject(navigator), m_Stepper(stepper)
        {
            connect(this, SIGNAL(SendStepper(mitk::Stepper * )), navigator, SLOT(SetStepper(mitk::Stepper * )));
            connect(this, SIGNAL(Refetch()), navigator, SLOT(Refetch()));
            emit SendStepper(stepper);
            
            m_ItkEventListener = new ItkEventListener(this);
            m_ObserverTag = m_Stepper->AddObserver(itk::ModifiedEvent(), m_ItkEventListener);
            
            emit Refetch();
        }
        
        StepperAdapter::~StepperAdapter()
        {
            m_ItkEventListener->Delete();
            m_Stepper->RemoveObserver(m_ObserverTag);
        }

        auto StepperAdapter::SetStepper(mitk::Stepper* stepper) -> void
        {
            this->SendStepper(stepper);
            this->Refetch();
        }
    }
}