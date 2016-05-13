#include "gmModuleViewer.hpp"

#include "gmColorTransferFunctionCanvas.hpp"
#include "gmDatamanager.hpp"
#include "gmImageNavigator.hpp"
#include "gmPiecewiseFunctionCanvas.hpp"
#include "gmProperties.hpp"
#include "gmSliderLevelWindowItem.hpp"
#include "gmStdMultiItem.hpp"
#include "gmTransferFunctionItem.hpp"
#include "gmMeasurementItem.hpp"
#include "gmPointListItem.hpp"
#include "gmMaskingItem.hpp"
#include "gmImageStatisticsItem.hpp"
#include "gmSubListManager.hpp"
#include "gmDataStorageListModel.hpp"
#include "gmPropertyController.hpp"
#include "gmNodeProperties.hpp"
#include "gmViewerController.hpp"
#include <mitkStandaloneDataStorage.h>

namespace gm
{
    namespace Module
    {

        auto Viewer::Initialize() -> void
        {
            log_trace(Log::Func);

            registerController(gm::Viewer::Controller::Create(), "viewer");

            mitk::DataStorage::Pointer storage = mitk::StandaloneDataStorage::New().GetPointer();
            ViewItem::StdMultiItem::SetDataStorage(storage);
            ViewItem::SliderLevelWindowItem::SetDataStorage(storage);
            ViewItem::MeasurementItem::SetDataStorage(storage);
            ViewItem::MaskingItem::SetDataStorage(storage);

            registerType<gm::ViewItem::DataStorageListModel>();

            registerController(new ViewItem::DataManager(storage), "Manager");
            registerController(new ViewItem::PropertyController(), "PropertyController");
            registerController(new ViewItem::NodeProperties(storage), "NodePropertyController");
            registerType<gm::ViewItem::ColorTransferFunctionCanvas>("GM", "ColorTransferFunctionCanvas");
            registerType<gm::ViewItem::DataManager>();
            registerType<gm::ViewItem::ImageNavigator>("GM", "ImageNavigator");
            registerType<gm::ViewItem::PiecewiseFunctionCanvas>("GM", "PiecewiseFunctionCanvas");
            registerType<gm::ViewItem::VolumeProperties>("GM", "VolumeProperties");
            registerType<gm::ViewItem::SliderLevelWindowItem>("GM", "SliderLevelWindowItem");
            registerType<gm::ViewItem::SliderNavigatorItem>("GM", "SliderNavigatorItem");
            registerType<gm::ViewItem::StdMultiItem>("GM", "StdMultiItem");
            registerType<gm::ViewItem::TransferFunctionItem>("GM", "TransferFunctionItem");
            registerType<gm::ViewItem::RenderWindowItem>("GM", "RenderWindowItem");
            registerType<gm::ViewItem::MeasurementItem>("GM", "MeasurementItem");
            registerType<gm::ViewItem::PointListItem>("GM", "PointListItem");
            registerType<gm::ViewItem::MaskingItem>("GM", "MaskingItem");
            registerType<gm::ViewItem::HistogramItem>("GM", "HistogramItem");
            registerType<gm::ViewItem::ImageStatisticsItem>("GM", "ImageStatisticsItem");
            registerType<gm::ViewItem::SubListManager>("GM", "ListManager");
        }
    }
}