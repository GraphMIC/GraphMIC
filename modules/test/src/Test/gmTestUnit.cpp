#include "gmTestUnit.hpp"

#include "gmNodeEditor.hpp"
#include "gmNodeGraph.hpp"
#include "gmNodeFactory.hpp"
#include "gmNodeObject.hpp"

#include "gmTestCase.hpp"
#include "gmTestController.hpp"

#include "gmNotificationController.hpp"

#include "gmAsync.hpp"
#include "gmLog.hpp"

#include <QJsonArray>

namespace gm
{
    namespace Test
    {
        Unit::Unit() : m_node(nullptr)
        {

        }

        auto Unit::FromJson(QJsonObject json) -> Unit*
        {
            log_trace(Log::Func);

            auto root = json["test"].toObject();
            auto name = root["name"].toString();
            auto prefix = root["prefix"].toString();
            auto exclude = root["exclude"].toBool();
            auto caseList = root["cases"].toArray();

            auto node = Node::Factory::Create(prefix + "::" + name);

            if (!node || exclude)
            {
                return nullptr;
            }

            log_info("node: " << node->getName().toStdString()
                     <<  " adress: " << &node);

            auto testUnit = new Unit();

            testUnit->m_node        = node;
            testUnit->m_name        = name;
            testUnit->m_prefix      = prefix;

            testUnit->m_node->moveToMain();
            testUnit->m_node->setDeletable(false);

            for (auto i = 0; i < caseList.count(); ++i)
            {
                testUnit->addCase(Case::FromJson(caseList.at(i)));
            }

            for (auto testCase : testUnit->m_cases)
            {
                testCase->setNode(testUnit->m_node);
                testCase->init();
            }

            return testUnit;
        }

        auto Unit::setNumber(int number) -> void
        {
            this->m_number = number;
        }

        auto Unit::getNumber() -> int
        {
            return this->m_number;
        }

        auto Unit::addCase(gm::Test::Case* testCase) -> void
        {
            if (!testCase)
            {
                return;
            }

            Async::MoveToMain(testCase);
            testCase->setTestUnit(this);
            testCase->setNumber(this->m_cases.count());

            this->m_cases.append(testCase);
        }

        auto Unit::onCaseFailed(Case* testCase) -> void
        {
            log_trace(Log::Func);

            if (!this->m_failedCases.contains(testCase))
            {
                this->m_failedCases.append(testCase);
                emit this->failedCountChanged();
            }
        }

        auto Unit::onCasePassed(Case* testCase) -> void
        {
            log_trace(Log::Func);

            if (!this->m_passedCases.contains(testCase))
            {
                this->m_passedCases.append(testCase);
                emit this->passedCountChanged();
            }
        }

        auto Unit::getCaseList() -> QQmlListProperty<Case>
        {
            return QQmlListProperty<Case>(this, this->m_cases);
        }

        auto Unit::onCaseSelected(Case* testCase) -> void
        {
            if (this->m_selectedCase)
            {
                this->m_selectedCase->setSelected(false);
            }

            this->m_selectedCase = testCase;
        }

        auto Unit::runThreaded() -> void
        {
            if (!this->m_node)
            {
                return;
            }

            if (this->m_running)
            {
                this->m_abort = true;
            }
            else
            {
                Async::Run([this](){
                    this->run();
                });
            }
        }
        auto Unit::run() -> void
        {
            if (!this->m_node)
            {
                return;
            }

            this->m_passedCases.clear();
            this->m_failedCases.clear();
            this->m_running = true;
            this->m_abort = false;

            emit this->passedCountChanged();
            emit this->failedCountChanged();
            emit this->runningChanged();

            for (auto testCase : this->m_cases)
            {
                if (this->m_abort)
                {
                    break;
                }

                testCase->run();
            }

            this->m_running = false;
            emit this->runningChanged();
        }

        auto Unit::activate() -> void
        {
            if (!this->m_active)
            {
                setActive(true);
            }
        }

        auto Unit::moveToNode() -> void
        {
            if (this->m_node)
            {
                Node::Editor::instance->moveToNode(this->m_node);
            }
        }

        auto Unit::setActive(bool active) -> void
        {
            if (this->m_active != active)
            {
                this->m_active = active;
                emit this->activeChanged();

                auto graph = Node::Editor::instance->getGraph();

                if (active)
                {
                    Controller::instance->setActiveUnit(this);

                    auto spawn = Node::Editor::instance->getSpawn();

                    this->m_node->setGeometry(spawn.x(), spawn.y(), 200, 0);

                    graph->addNode(this->m_node);
                }
                else
                {
                    graph->removeNode(this->m_node);
                }
            }
        }

        auto Unit::isActive() -> bool
        {
            return this->m_active;
        }

        auto Unit::getFailedCount() -> int
        {
            return this->m_failedCases.count();
        }

        auto Unit::getPassedCount() -> int
        {
            return this->m_passedCases.count();
        }

        auto Unit::getName() -> QString
        {
            return this->m_name;
        }

        auto Unit::getPrefix() -> QString
        {
            return this->m_prefix;
        }

        auto Unit::isRunning() -> bool
        {
            return this->m_running;
        }

        auto Unit::getNode() -> Node::Object*
        {
            return this->m_node;
        }
    }
}
