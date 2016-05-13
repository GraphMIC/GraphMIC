#include "gmLog.hpp"
#include "gmDebugController.hpp"

namespace gm
{
    namespace Debug
    {
        Controller* Controller::instance = nullptr;
        
        int Controller::connectionViewCount = -1;
        int Controller::notificationCount   = 0;
        int Controller::constraintCount     = 0;
        int Controller::connectionCount     = 0;
        int Controller::logicCount          = 0;
        int Controller::imageCount          = 0;
        int Controller::nodeCount           = 0;
        int Controller::compCount           = 0;
        int Controller::dataCount           = 0;
        
        Controller::Controller()
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
        
        auto Controller::setDebugUI(bool debugUI) -> void
        {
            if (this->m_debugUI != debugUI)
            {
                this->m_debugUI = debugUI;
                emit this->debugUIChanged();
            }
        }
        
        auto Controller::getDebugUI() -> bool
        {
            return this->m_debugUI;
        }
                
        auto Controller::incNodeCount() -> void
        {
            ++nodeCount;
            emit this->nodeCountChanged();
        }
        
        auto Controller::decNodeCount() -> void
        {
            --nodeCount;
            emit this->nodeCountChanged();
        }
        
        auto Controller::getNodeCount() -> int
        {
            return nodeCount;
        }
        
        auto Controller::incDataCount() -> void
        {
            ++dataCount;
            emit this->dataCountChanged();
        }

        auto Controller::decDataCount() -> void
        {
            --dataCount;
            emit this->dataCountChanged();
        }
        
        auto Controller::getDataCount() -> int
        {
            return dataCount;
        }
        
        auto Controller::incImageCount() -> void
        {
            ++imageCount;
            emit this->imageCountChanged();
        }
        
        auto Controller::decImageCount() -> void
        {
            --imageCount;
            emit this->imageCountChanged();
        }
        
        auto Controller::getImageCount() -> int
        {
            return imageCount;
        }
        
        auto Controller::incCompCount() -> void
        {
            ++compCount;
            emit this->compCountChanged();
        }
        
        auto Controller::decCompCount() -> void
        {
            --compCount;
            emit this->compCountChanged();
        }
        
        auto Controller::getCompCount() -> int
        {
            return compCount;
        }
        
        auto Controller::incLogicCount() -> void
        {
            ++logicCount;
            emit this->logicCountChanged();
        }
        
        auto Controller::decLogicCount() -> void
        {
            --logicCount;
            emit this->logicCountChanged();
        }
        
        auto Controller::getLogicCount() -> int
        {
            return logicCount;
        }
        
        auto Controller::incConstraintCount() -> void
        {
            ++constraintCount;
            emit constraintCountChanged();
        }
        
        auto Controller::decConstraintCount() -> void
        {
            --constraintCount;
            emit this->constraintCountChanged();
        }
        
        auto Controller::getConstraintCount() -> int
        {
            return constraintCount;
        }
        
        auto Controller::incNotificationCount() -> void
        {
            ++notificationCount;
            emit this->notificationCountChanged();
        }
        
        auto Controller::decNotificationCount() -> void
        {
            --notificationCount;
            emit this->notificationCountChanged();
        }
        
        auto Controller::getNotificationCount() -> int
        {
            return notificationCount;
        }
        
        auto Controller::incConnectionCount() -> void
        {
            ++connectionCount;
            emit this->connectionCountChanged();
        }
        
        auto Controller::decConnectionCount() -> void
        {
            --connectionCount;
            emit this->connectionCountChanged();
        }
        
        auto Controller::getConnectionCount() -> int
        {
            return connectionCount;
        }
        
        auto Controller::incConnectionViewCount() -> void
        {
            ++connectionViewCount;
            emit this->connectionViewCountChanged();
        }
        
        auto Controller::decConnectionViewCount() -> void
        {
            --connectionViewCount;
            emit this->connectionViewCountChanged();
        }
        
        auto Controller::getConnectionViewCount() -> int
        {
            return connectionViewCount;
        }
    }
}