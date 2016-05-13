#pragma once

#include <QQmlListProperty>
#include <QObject>
#include <QHash>

namespace gm
{
    namespace Node
    {
        class Object;
    }
    
    namespace Test
    {
        class List;
        class Instance;
        class Unit;
        
        class Controller : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QQmlListProperty<gm::Test::Unit> units READ getUnitList NOTIFY unitListChanged);
            Q_PROPERTY(QString stateString READ getStateString NOTIFY stateStringChanged);
            Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged);
            Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged);
        private:
            QList<Unit*> m_units;
            QString m_stateString;
            Unit* m_activeUnit = nullptr;
            bool m_abort = false;;
            bool m_running = false;
            bool m_loading = false;
            Controller();
        public:
            static Controller* instance;
            static auto Create() -> Controller*;
            auto getUnitList() -> QQmlListProperty<Unit>;
            auto setStateString(const QString&) -> void;
            auto getStateString() -> QString;
            auto setActiveUnit(Unit*) -> void;
            auto setLoading(bool) -> void;
            auto isLoading() -> bool;
            auto setRunning(bool) -> void;
            auto isRunning() -> bool;
        public slots:
            void init();
            void runUnits();
        signals:
            void stateStringChanged();
            void unitListChanged();
            void runningChanged();
            void loadingChanged();
        };
    }
}