#pragma once

#include <QQmlListProperty>
#include <QJsonObject>
#include <QObject>

namespace gm
{
    namespace Node
    {
        class Object;
    }

    namespace Test
    {
        class Case;

        class Unit : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QQmlListProperty<gm::Test::Case> cases READ getCaseList NOTIFY casesChanged);
            Q_PROPERTY(QString name READ getName CONSTANT);
            Q_PROPERTY(QString prefix READ getPrefix CONSTANT);
            Q_PROPERTY(int failedCount READ getFailedCount NOTIFY failedCountChanged);
            Q_PROPERTY(int passedCount READ getPassedCount NOTIFY passedCountChanged);
            Q_PROPERTY(int number READ getNumber CONSTANT);
            Q_PROPERTY(bool active READ isActive NOTIFY activeChanged);
            Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged);
        private:
            QList<Case*> m_cases;
            QList<Case*> m_failedCases;
            QList<Case*> m_passedCases;
            Node::Object* m_node;
            Case* m_selectedCase = nullptr;
            QString m_prefix;
            QString m_name;
            bool m_abort = false;
            bool m_running = false;
            bool m_active = false;
            int m_number = 0;
        private:
            Unit();
            auto getCaseList() -> QQmlListProperty<Case>;
            auto addCase(Case*) -> void;
            auto getName() -> QString;
            auto getPrefix() -> QString;
            auto getFailedCount() -> int;
            auto getPassedCount() -> int;
            auto isRunning() -> bool;
            auto getNumber() -> int;
        public:
            static auto FromJson(QJsonObject) -> Unit*;
            auto setNumber(int) -> void;
            auto setActive(bool) -> void;
            auto getNode() -> Node::Object*;
            auto isActive() -> bool;
            auto onCaseFailed(Case*) -> void;
            auto onCasePassed(Case*) -> void;
            auto onCaseSelected(Case*) -> void;
        public slots:
            void run();
            void runThreaded();
            void activate();
            void moveToNode();
        signals:
            void runningChanged();
            void failedCountChanged();
            void passedCountChanged();
            void activeChanged();
            void casesChanged();
        };
    }
}