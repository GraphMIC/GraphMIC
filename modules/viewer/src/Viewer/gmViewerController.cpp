#include "gmViewerController.hpp"

#include "gmLog.hpp"
#include "gmDataBase.hpp"
#include "gmDatamanager.hpp"
#include "gmAppContextController.hpp"
#include "gmAppContextBase.hpp"
#include "gmDataImage.hpp"

#include <mitkStandaloneDataStorage.h>
#include <mitkProperties.h>
#include <mitkRenderingManager.h>

namespace gm
{
    namespace Viewer
    {
        Controller* Controller::instance = nullptr;

        Controller::Controller() : m_empty(true)
        {
            log_trace(Log::New, this);

            if (instance)
            {
                throw "instance already existing";
            }

            instance = this;

        }

        auto Controller::Create() -> Controller*
        {
            return new Controller();
        }

        auto Controller::setEmpty(bool empty) -> void
        {
            log_trace (Log::Set, empty);

            if (this->m_empty != empty)
            {
                this->m_empty = empty;
                emit this->emptyChanged();
            }
        }

        auto Controller::getEmpty() -> bool
        {
            return this->m_empty;
        }

        auto Controller::addImage(Data::Image* image) -> void
        {
            log_trace(Log::Func, image);

            if (!image)
            {
                this->setEmpty(true);
                return;
            }

            auto mitkImage  = image->getMitkImage();
            auto mitkNode   = image->getMitkDataNode();

            if (gm::ViewItem::DataManager::instance->getDataStorage()->Exists(mitkNode))
            {
                log_error("mitkDataNode is already in data storage"); //todo: handle this case properly
                return;
            }

            mitkNode->SetBoolProperty("image", mitk::BoolProperty::New(true));

            gm::ViewItem::DataManager::instance->getDataStorage()->Add(mitkNode);
            this->setEmpty(false);
        }

        void Controller::updateBoundingObjects()
        {
            mitk::RenderingManager::GetInstance()->InitializeViewsByBoundingObjects(gm::ViewItem::DataManager::instance->getDataStorage());
        }

        Controller::~Controller()
        {
            log_trace(Log::Del, this);
        }
    }
}
