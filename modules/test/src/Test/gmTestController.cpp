#include "gmTestController.hpp"
#include "gmTestUnit.hpp"
#include "gmTestImageProvider.hpp"
#include "gmNodeObject.hpp"
#include "gmNodeEditor.hpp"

#include "gmIOFile.hpp"
#include "gmIOJson.hpp"

#include "gmAsync.hpp"
#include "gmApp.hpp"
#include "gmLog.hpp"

namespace gm
{
    namespace Test
    {
        Controller* Controller::instance = nullptr;
        
        Controller::Controller()
        {
            if (instance)
            {
                throw "instance already existing";
            }

            this->m_loading = false;
            instance = this;
        }
        
        auto Controller::Create() -> Controller*
        {
            return new Controller();
        }
            
        auto Controller::init() -> void
        {
            Node::Editor::instance->setShortcutsEnabled(false);

            Async::Run([this](){

                this->setLoading(true);

                this->setStateString("Loading Test Image Data...");

                ImageProvider::Create();

                this->setStateString("Loading Test Units...");

                auto configPath = Application::instance->getResourceDir() + "/tests/config/";

                QStringList filePathList = IO::File::GetFilesFromDirectory(configPath, ".json");

                for (auto path : filePathList)
                {
                    auto testUnit = Unit::FromJson(IO::Json::FromFile(path));

                    if (testUnit)
                    {
                        testUnit->setNumber(this->m_units.count());
                        Async::MoveToMain(testUnit);
                        this->m_units.append(testUnit);
                        emit this->unitListChanged();
                    }
                }

                this->setLoading(false);

                this->setStateString("Ready");
            });
        }

        auto Controller::setStateString(const QString& stateString) -> void
        {
            this->m_stateString = stateString;
            emit this->stateStringChanged();
        }

        auto Controller::getStateString() -> QString
        {
            return this->m_stateString;
        }

        auto Controller::setLoading(bool loading) -> void
        {
            if (this->m_loading != loading)
            {
                this->m_loading = loading;
                emit this->loadingChanged();
            }
        }

        auto Controller::isLoading() -> bool
        {
            return this->m_loading;
        }

        auto Controller::setActiveUnit(Unit* testUnit) -> void
        {
            if (this->m_activeUnit)
            {
                this->m_activeUnit->setActive(false);
            }

            this->m_activeUnit = testUnit;
        }

        auto Controller::runUnits() -> void
        {
            log_trace(Log::Func);

            if (this->m_running)
            {
                this->m_abort = true;
            }
            else
            {
                this->setRunning(true);
                this->m_abort = false;

                Async::Run([this](){
                    for (auto testUnit : this->m_units)
                    {
                        if (this->m_abort)
                        {
                            break;
                        }
                        
                        Async::Synchronize([testUnit](){
                            testUnit->activate();
                        });

                        testUnit->run();
                    }

                    this->setRunning(false);
                });
            }
        }

        auto Controller::setRunning(bool running) -> void
        {
            if (this->m_running != running)
            {
                this->m_running = running;
                emit this->runningChanged();
            }
        }
        auto Controller::isRunning() -> bool
        {
            return this->m_running;
        }

        auto Controller::getUnitList() -> QQmlListProperty<Unit>
        {
            return QQmlListProperty<Unit>(this, this->m_units);
        }
    }
}