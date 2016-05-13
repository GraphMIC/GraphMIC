#pragma once

#include "gmViewerExport.hpp"

#include "mitkRenderingManager.h"

#include <QObject>
#include <QEvent>

namespace gm
{
    namespace ViewItem
    {
        class RenderingManagerFactory;
        
        class GM_VIEWER_EXPORT RenderingManager: public QObject, public mitk::RenderingManager
        {
            Q_OBJECT
        public:
            mitkClassMacro(RenderingManager, mitk::RenderingManager );
            virtual ~RenderingManager();
            virtual auto event( QEvent *event ) -> bool;
        protected:
            itkFactorylessNewMacro(Self);
            RenderingManager();
            virtual auto GenerateRenderingRequestEvent() -> void;
            virtual auto StartOrResetTimer() -> void;
            int pendingTimerCallbacks;
        protected slots:
            void timerCallback();
        private:
            friend class RenderingManagerFactory;
            auto myUpdateExecutePendingRequests() -> void;
        };
        
        class QmlMitkRenderingRequestEvent : public QEvent
        {
        public:
            enum Type
            {
                RenderingRequest = QEvent::MaxUser - 1024
            };
            
            QmlMitkRenderingRequestEvent(): QEvent( (QEvent::Type) RenderingRequest ) {};
        };
    }
}
