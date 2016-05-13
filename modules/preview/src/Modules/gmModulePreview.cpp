#include "gmModulePreview.hpp"

#include "gmPreviewController.hpp"
#include "gmPreviewImageViewer.hpp"
#include "gmPreviewVectorViewer.hpp"
#include "gmPreviewNumberViewer.hpp"
#include "gmPreviewPointsetViewer.hpp"

namespace gm
{
    namespace Module
    {
        auto Preview::Initialize() -> void
        {
            log_trace(Log::Func);

            registerController(gm::Preview::Controller::Create(), "preview");
            registerType<gm::Preview::ImageViewer>("org.graphmic.preview", "ImageViewer");
            registerType<gm::Preview::VectorViewer>("org.graphmic.preview", "VectorViewer");
            registerType<gm::Preview::NumberViewer>("org.graphmic.preview", "NumberViewer");
            registerType<gm::Preview::PointsetViewer>("org.graphmic.preview", "PointsetViewer");
        }
    }
}
