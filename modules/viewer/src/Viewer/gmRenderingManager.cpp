#include "gmRenderingManager.hpp"
#include "gmRenderWindowItem.hpp"
#include <QTimer>

namespace gm
{
    namespace ViewItem
    {
        RenderingManager::RenderingManager() : pendingTimerCallbacks(0)
        {
        }
        
        RenderingManager::~RenderingManager()
        {
        }
        
        auto RenderingManager::GenerateRenderingRequestEvent() -> void
        {
            QCoreApplication::postEvent(this, new QmlMitkRenderingRequestEvent);
        }
        
        auto RenderingManager::StartOrResetTimer() -> void
        {
            QTimer::singleShot(200, this, SLOT(timerCallback()));
            pendingTimerCallbacks++;
        }
        
        auto RenderingManager::timerCallback() -> void
        {
            if(!--pendingTimerCallbacks)
            {
                this->ExecutePendingHighResRenderingRequest();
            }
        }

        auto RenderingManager::event(QEvent* event) -> bool
        {
            if(event->type() == (QEvent::Type) QmlMitkRenderingRequestEvent::RenderingRequest)
            {
                // Directly process all pending rendering requests
                //this->ExecutePendingRequests();
                this->myUpdateExecutePendingRequests();
                
                return true;
            }
            
            return false;
        }

        auto RenderingManager::myUpdateExecutePendingRequests() -> void
        {
            m_UpdatePending = false;
            
            // Satisfy all pending update requests
            RenderWindowList::iterator it;
            int i = 0;
            for(it = m_RenderWindowList.begin(); it != m_RenderWindowList.end(); ++it, ++i)
            {
                if(it->second == RENDERING_REQUESTED)
                {
                    vtkRenderWindow* renderWindow = it->first;
                    
                    // If the renderWindow is not valid, we do not want to inadvertantly create
                    // an entry in the m_RenderWindowList map. It is possible if the user is
                    // regularly calling AddRenderer and RemoveRenderer for a rendering update
                    // to come into this method with a renderWindow pointer that is valid in the
                    // sense that the window does exist within the application, but that
                    // renderWindow has been temporarily removed from this RenderingManager for
                    // performance reasons.
                    if(m_RenderWindowList.find(renderWindow) == m_RenderWindowList.end())
                    {
                        continue;
                    }
                    
                    // Erase potentially pending requests for this window
                    m_RenderWindowList[renderWindow] = RENDERING_INACTIVE;
                    
                    m_UpdatePending = false;
                    
                    // Immediately repaint this window (implementation platform specific)
                    // If the size is 0 it crahses
                    int* size = renderWindow->GetSize();
                    if(0 != size[0] && 0 != size[1])
                    {
                        RenderWindowItem* qqi = RenderWindowItem::GetInstanceForVTKRenderWindow(renderWindow);
                        if(qqi)
                        {
                            qqi->update();
                        }
                    }
                }
            }
        }
    }
}

