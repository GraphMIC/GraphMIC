#pragma once

#include "gmViewerExport.hpp"
#include "gmInterfaceViewerController.hpp"

namespace gm
{
    namespace Viewer
    {
        class ViewItem;
        
        class GM_VIEWER_EXPORT Controller : public Interface::Viewer::Controller
        {
            Q_OBJECT
            Q_PROPERTY(bool empty READ getEmpty NOTIFY emptyChanged);
        public:
            bool m_empty;
            static Controller* instance;
        private:
            auto setEmpty(bool) -> void;
        public:
            Controller();
            auto addImage(Data::Image*) -> void override;
            auto getEmpty() -> bool;
            auto releaseNode() -> void;
            static auto Create() -> Controller*;
            ~Controller();
        public slots:
            void updateBoundingObjects();
        signals:
            void emptyChanged();
        };
    }
}
