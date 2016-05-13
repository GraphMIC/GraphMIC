#pragma once

#include "gmCoreExport.hpp"
#include "gmNodeSelectable.hpp"

#include <functional>
#include <QElapsedTimer>
#include <QPoint>
#include <QHash>

namespace gm
{
    namespace Notification
    {
        class Entry;
    }
    
    namespace Slot
    {
        class InputList;
        class OutputList;
        class InputBase;
        class OutputBase;
    }
    
    namespace Logic
    {
        class Base;
    }
    
    namespace Param
    {
        class GroupList;
        class Group;
    }
    
    namespace Component
    {
        class Base;
    }

    namespace Node
    {
        class Graph;
        
        class GM_CORE_EXPORT Object : public Selectable
        {
            Q_OBJECT
            Q_PROPERTY(gm::Slot::OutputList* outputList READ getOutputList CONSTANT);
            Q_PROPERTY(gm::Param::GroupList* groupList READ getGroupList CONSTANT);
            Q_PROPERTY(gm::Slot::InputList* inputList READ getInputList CONSTANT);
            Q_PROPERTY(bool forceExecution READ getForceExecution WRITE setForceExecution NOTIFY forceExecutionChanged);
            Q_PROPERTY(bool threaded READ getThreaded WRITE setThreaded NOTIFY threadedChanged);
            Q_PROPERTY(bool deletable READ isDeletable NOTIFY deletableChanged);
            Q_PROPERTY(bool useTimer READ getUseTimer NOTIFY useTimerChanged);
            Q_PROPERTY(bool expanded READ getExpanded NOTIFY expandedChanged);
            Q_PROPERTY(bool runnable READ isRunnable NOTIFY runnableChanged);
            Q_PROPERTY(bool modified READ isModified NOTIFY modifiedChanged);
            Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged);
            Q_PROPERTY(bool valid READ getValid NOTIFY validChanged);
            Q_PROPERTY(int errorCount READ getErrorCount NOTIFY errorCountChanged);
            Q_PROPERTY(int layer READ getLayer NOTIFY layerChanged);
            Q_PROPERTY(int time READ getTime NOTIFY timeChanged);
            Q_PROPERTY(QPoint position READ getPosition CONSTANT);
            Q_PROPERTY(QPoint size READ getSize CONSTANT);
            Q_PROPERTY(QString docLink READ getDocLink CONSTANT);
            Q_PROPERTY(QString name READ getName CONSTANT);
            Q_PROPERTY(QString lib READ getLib CONSTANT);
        private:
            friend class Logic::Base;
            QHash<QString, Component::Base*> m_components;
            QList<Notification::Entry*> m_notifications;
            Slot::InputList* m_inputList;
            Slot::OutputList* m_outputList;
            Param::GroupList* m_groupList;
            QElapsedTimer m_timer;
            Logic::Base* m_logic;
            QPoint m_position;
            QPoint m_size;
            QString m_name;
            QString m_lib;
            Graph* m_graph      = nullptr;
            bool m_forceExecution = false;
            bool m_isDataSource = false;
            bool m_deletable    = true;
            bool m_threaded     = true;
            bool m_useTimer     = false;
            bool m_expanded     = true;
            bool m_runnable     = false;
            bool m_modified     = true;
            bool m_running      = false;
            bool m_valid        = true;
            int m_layer         = 0;
            int m_time          = 0;
            int m_errorCount    = 0;
        public:
            std::function<void(void)> successFunction;
            std::function<void(const QString&, Object*)> failureFunction;
        private:
            auto getOutputList() -> Slot::OutputList*;
            auto getGroupList() -> Param::GroupList*;
            auto getInputList() -> Slot::InputList*;
        public:
            Object() = delete;
            Object(Logic::Base*);
            auto getComponents() -> QList<Component::Base*>;
            auto getComponentMap() -> QHash<QString, Component::Base*>;
            auto getOutputs() -> QList<Slot::OutputBase*>;
            auto addNotification(Notification::Entry*) -> void;
            auto setIsDataSource(bool) -> void;
            auto isDataSource() -> bool;
            auto setRunning(bool) -> void;
            auto isRunning() -> bool;
            auto setGraph(Graph*) -> void;
            auto getGraph() -> Graph*;
            auto getLogic() -> Logic::Base*;
            auto setForceExecution(bool) -> void;
            auto getForceExecution() -> bool;
            auto setThreaded(bool) -> void;
            auto getThreaded() -> bool;
            auto setUseTimer(bool) -> void;
            auto getUseTimer() -> bool;
            auto setExpanded(bool) -> void;
            auto getExpanded() -> bool;
            auto getPosition() -> QPoint;
            auto getSize() -> QPoint;
            auto setLayer(int) -> void;
            auto getLayer() -> int;
            auto setTime(int) -> void;
            auto getTime() -> int;
            auto setErrorCount(int) -> void;
            auto getErrorCount() -> int;
            auto deleteObject() -> void override;
            auto setValid(bool) -> void;
            auto getValid() -> bool;
            auto setRunnable(bool) -> void;
            auto isRunnable() -> bool;
            auto setModified(bool) -> void;
            auto isModified() -> bool;
            auto getDocLink() -> QString;
            auto getName() -> QString;
            auto getLib() -> QString;
            auto executeTask() -> void;
            auto moveToMain() -> void;
            auto setDeletable(bool) -> void;
            auto isDeletable() -> bool;
            ~Object();
        public slots:
            void toggleExpansion();
            void setGeometry(int, int, int, int);
            void centerView();
            void remove();
            void raise();
            void execute();
        signals:
            void forceExecutionChanged();
            void errorCountChanged();
            void deletableChanged();
            void threadedChanged();
            void useTimerChanged();
            void runnableChanged();
            void modifiedChanged();
            void expandedChanged();
            void updateGeometry();
            void runningChanged();
            void validChanged();
            void layerChanged();
            void timeChanged();
        };
    }
}
