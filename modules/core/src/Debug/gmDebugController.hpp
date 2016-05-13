#pragma once

#include <QObject>

namespace gm
{
    namespace Debug
    {
        class Controller : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(int connectionViewCount READ getConnectionViewCount NOTIFY connectionViewCountChanged);
            Q_PROPERTY(int notificationCount READ getNotificationCount NOTIFY notificationCountChanged);
            Q_PROPERTY(int constraintCount READ getConstraintCount NOTIFY constraintCountChanged);
            Q_PROPERTY(int connectionCount READ getConnectionCount NOTIFY connectionCountChanged);
            Q_PROPERTY(int logicCount READ getLogicCount NOTIFY logicCountChanged);
            Q_PROPERTY(int imageCount READ getImageCount NOTIFY imageCountChanged);
            Q_PROPERTY(int nodeCount READ getNodeCount NOTIFY nodeCountChanged);
            Q_PROPERTY(int compCount READ getCompCount NOTIFY compCountChanged);
            Q_PROPERTY(int dataCount READ getDataCount NOTIFY dataCountChanged);
            Q_PROPERTY(bool debugUI READ getDebugUI WRITE setDebugUI NOTIFY debugUIChanged);
        private:
            static int connectionViewCount;
            static int notificationCount;
            static int constraintCount;
            static int connectionCount;
            static int logicCount;
            static int imageCount;
            static int nodeCount;
            static int compCount;
            static int dataCount;
            bool m_debugUI = false;
        private:
            Controller();
        public:
            static Controller* instance;
            static auto Create() -> Controller*;
            auto setDebugUI(bool) -> void;
            auto getDebugUI() -> bool;
            auto incDataCount() -> void;
            auto decDataCount() -> void;
            auto getDataCount() -> int;
            auto incNodeCount() -> void;
            auto decNodeCount() -> void;
            auto getNodeCount() -> int;
            auto incCompCount() -> void;
            auto decCompCount() -> void;
            auto getCompCount() -> int;
            auto incLogicCount() -> void;
            auto decLogicCount() -> void;
            auto getLogicCount() -> int;
            auto incImageCount() -> void;
            auto decImageCount() -> void;
            auto getImageCount() -> int;
            auto incConnectionCount() -> void;
            auto decConnectionCount() -> void;
            auto getConnectionCount() -> int;
            auto incConstraintCount() -> void;
            auto decConstraintCount() -> void;
            auto getConstraintCount() -> int;
            auto incNotificationCount() -> void;
            auto decNotificationCount() -> void;
            auto getNotificationCount() -> int;
            auto incConnectionViewCount() -> void;
            auto decConnectionViewCount() -> void;
            auto getConnectionViewCount() -> int;
        signals:
            void connectionViewCountChanged();
            void notificationCountChanged();
            void constraintCountChanged();
            void connectionCountChanged();
            void logicCountChanged();
            void imageCountChanged();
            void compCountChanged();
            void nodeCountChanged();
            void dataCountChanged();
            void debugUIChanged();
        };
    }
}
