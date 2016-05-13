#include "gmNodeObject.hpp"

#include "gmAsync.hpp"
#include "gmNodeList.hpp"
#include "gmLogicBase.hpp"
#include "gmNodeGraph.hpp"
#include "gmNodeEditor.hpp"
#include "gmNodeFactory.hpp"

#include "gmParamGroupList.hpp"

#include "gmSlotInputList.hpp"
#include "gmSlotOutputList.hpp"
#include "gmSlotInputBase.hpp"
#include "gmSlotOutputBase.hpp"

#include "gmNotificationEntry.hpp"
#include "gmNotificationController.hpp"
#include "gmNodePropertyController.hpp"

#include "gmInterfacePreviewController.hpp"
#include "gmDebugController.hpp"

namespace gm
{
    namespace Node
    {
        Object::Object(Logic::Base* logic) : m_logic(logic)
        {
            log_trace(Log::New, this);
            
            this->m_name        = logic->getName();
            this->m_lib         = logic->getLib();
            this->m_inputList   = new Slot::InputList();
            this->m_outputList  = new Slot::OutputList();
            this->m_groupList   = new Param::GroupList();
            this->m_size        = QPoint(200, 0);

            Debug::Controller::instance->incNodeCount();
        }

        auto Object::setDeletable(bool deletable) -> void
        {
            if (this->m_deletable != deletable)
            {
                this->m_deletable = deletable;
                emit this->deletableChanged();
            }
        }

        auto Object::isDeletable() -> bool
        {
            return this->m_deletable;
        }

        auto Object::setErrorCount(int errorCount) -> void
        {
            log_trace(Log::Set, errorCount);

            if (this->m_errorCount != errorCount)
            {
                this->m_errorCount = errorCount;
                emit this->errorCountChanged();
            }
        }

        auto Object::getErrorCount() -> int
        {
            return this->m_errorCount;
        }

        auto Object::addNotification(Notification::Entry* entry) -> void
        {
            log_trace(Log::Func, entry);
            
            this->m_notifications.append(entry);
            this->setErrorCount(this->m_notifications.count());
        }
        
        auto Object::getOutputs() -> QList<Slot::OutputBase*>
        {
            return this->m_outputList->getSlots();
        }
        
        auto Object::getComponents() -> QList<Component::Base*>
        {
            return this->m_components.values();
        }
        
        auto Object::getComponentMap() -> QHash<QString, Component::Base*>
        {
            return this->m_components;
        }
        
        auto Object::setIsDataSource(bool isDataSource) -> void
        {
            log_trace(Log::Set, isDataSource);
            
            this->m_isDataSource = isDataSource;
        }
        
        auto Object::isDataSource() -> bool
        {
            return this->m_isDataSource;
        }
        
        auto Object::setGraph(Graph* graph) -> void
        {
            log_trace(Log::Set, graph);
            
            this->m_graph = graph;
        }
        
        auto Object::getGraph() -> Graph*
        {
            return this->m_graph;
        }
        
        auto Object::getLogic() -> Logic::Base*
        {
            return this->m_logic;
        }
        
        auto Object::setRunning(bool running) -> void
        {
            log_trace(Log::Set, running);
            
            if (this->m_running != running)
            {
                this->m_running = running;
                emit this->runningChanged();
            }
        }
        
        auto Object::isRunning() -> bool
        {
            return this->m_running;
        }
    
        auto Object::setUseTimer(bool useTimer) -> void
        {
            log_trace(Log::Set, useTimer);
            
            if (this->m_useTimer != useTimer)
            {
                this->m_useTimer = useTimer;
                emit this->useTimerChanged();
            }
        }
        
        auto Object::getUseTimer() -> bool
        {
            return this->m_useTimer;
        }
        
        auto Object::remove() -> void
        {
            log_trace(Log::Func, this);
            
            if (this->m_running || !this->m_deletable)
            {
                return;
            }

            this->deleteObject();
        }
                                
        auto Object::setExpanded(bool expanded) -> void
        {
            log_trace(Log::Set, expanded);
            
            if (this->m_expanded != expanded)
            {
                this->m_expanded = expanded;
                emit this->expandedChanged();
            }
        }
                
        auto Object::getExpanded() -> bool
        {
            return this->m_expanded;
        }
                
        auto Object::toggleExpansion() -> void
        {
            log_trace(Log::Func);
            
            this->m_expanded = !this->m_expanded;
            emit this->expandedChanged();
        }
                
        auto Object::setGeometry(int x, int y, int w, int h) -> void
        {
            log_trace(Log::Func);
            
            this->m_position.setX(x);
            this->m_position.setY(y);
            this->m_size.setX(w);
            this->m_size.setY(h);
        }
        
        auto Object::setTime(int timeInMs) -> void
        {
            log_trace(Log::Set, timeInMs);
            
            this->m_time = timeInMs;
            emit this->timeChanged();
        }
        
        auto Object::getTime() -> int
        {
            return this->m_time;
        }
        
        auto Object::getSize() -> QPoint
        {
            return this->m_size;
        }
        
        auto Object::getPosition() -> QPoint
        {
            return this->m_position;
        }
        
        auto Object::deleteObject() -> void
        {
            log_trace(Log::Func, this);

            if (this->m_deletable)
            {
                this->m_graph->deleteNode(this);
            }
        }
        
        auto Object::setLayer(int layer) -> void
        {
            this->m_layer = layer;
            emit this->layerChanged();
        }
        
        auto Object::raise() -> void
        {
            log_trace(Log::Func);
            
            this->m_graph->raiseNode(this);
            PropertyController::instance->setNode(this);
        }

        auto Object::getLayer() -> int
        {
            return this->m_layer;
        }
        
        auto Object::centerView() -> void
        {
            log_trace(Log::Func, this);
            
            emit this->updateGeometry();
            emit Editor::instance->moveToNode(this);
        }
        
        auto Object::execute() -> void
        {
            log_trace(Log::Func, this);
            
            if (this->m_threaded)
            {
                Async::Run([this](){
                    this->executeTask();
                });;
            }
            else
            {
                this->executeTask();
            }
        }

        auto Object::setForceExecution(bool forceExecution) -> void
        {
            if (this->m_forceExecution != forceExecution)
            {
                this->m_forceExecution = forceExecution;
                emit this->forceExecutionChanged();
            }
        }

        auto Object::getForceExecution() -> bool
        {
            return this->m_forceExecution;
        }
        
        auto Object::executeTask() -> void
        {
            log_trace(Log::Func, this);

            if (!this->m_forceExecution)
            {
                if (!this->m_modified && !this->m_isDataSource)
                {
                    return;
                }
            }
            
            setValid(true);
            
            bool readyToExecute = true;
            
            for (auto input : this->m_inputList->getSlots())
            {
                if (input->isRequired() && !input->isConnected())
                {
                    if (this->failureFunction)
                    {
                        this->failureFunction("Node \'" + this->getName() + "\': required input \'" + input->getName() + "\' is not connected to an output.", this);
                    }
                    else
                    {
                        Async::Synchronize([this, input](){
                            Notification::Controller::Post(Notification::Type::Error, "required input \'" + input->getName() + "\' is not connected to an output.", this);
                        });
                    }

                    readyToExecute = false;
                }
            }
            
            for (auto slot : this->m_outputList->getSlots())
            {
                slot->clear();
            }
            
            if (!readyToExecute)
            {
                setValid(false);
                return;
            }
            
            this->setTime(0);
            this->m_timer.restart();
            this->setRunning(true);

            bool success = true;
            QString errorMessage;
            
            try
            {
                this->m_logic->run();
            }
            
            catch (std::runtime_error* e)
            {
                log_exception("throw std::runtime_error: " << e->what());

                errorMessage = e->what();
                success = false;
            }
                
            catch (const mitk::Exception& e)
            {
                log_exception("throw mitk::Exception: " << e.what());

                errorMessage = e.what();
                success = false;
            }

            catch (cv::Exception& e)
            {
                log_exception("throw itk::ExceptionObject: " << e.what());

                errorMessage = e.what();
                success = false;
            }

            catch (const itk::ExceptionObject& e)
            {
                log_exception("throw itk::ExceptionObject: " << e.what());

                errorMessage = e.what();
                success = false;
            }

            if (success)
            {
                this->setModified(false);
                this->setTime(this->m_timer.elapsed());

                if (this->successFunction)
                {
                    this->successFunction();
                }

                if (Interface::Preview::Controller::instance->getNode() == this)
                {
                    Async::Synchronize([this](){
                        Interface::Preview::Controller::instance->onNodeDataChanged();

                        for (auto output : this->m_outputList->getSlots())
                        {
                            emit output->dataChanged();
                        }
                    });
                }
            }
            else
            {
                this->setValid(false);
                this->setRunning(false);
                this->setModified(true);
                this->setTime(0);

                if (this->failureFunction)
                {
                    this->failureFunction(errorMessage, this);
                } else {
                    Notification::Controller::Post(Notification::Type::Error, errorMessage, this);
                }
            }

            this->setRunning(false);
        }

        auto Object::moveToMain() -> void
        {
            log_trace(Log::Func);
            
            this->m_outputList->moveToMain();
            this->m_inputList->moveToMain();
            this->m_groupList->moveToMain();

            Async::MoveToMain(this);
        }
        
        auto Object::getInputList() -> Slot::InputList*
        {
            return this->m_inputList;
        }
                
        auto Object::getGroupList() -> Param::GroupList*
        {
            return this->m_groupList;
        }
                
        auto Object::getOutputList() -> Slot::OutputList*
        {
            return this->m_outputList;
        }

        auto Object::getName() -> QString
        {
            return this->m_name;
        }

        auto Object::getDocLink() -> QString
        {
            return this->m_logic->getDocLink();
        }
                
        auto Object::getLib() -> QString
        {
            return this->m_lib;
        }
                
        auto Object::setModified(bool modified) -> void
        {
            log_trace(Log::Set, modified);

            if (this->m_graph && modified)
            {
                this->m_graph->setModified(true);
            }

            if (this->m_modified != modified)
            {
                this->m_modified = modified;
                emit this->modifiedChanged();
                
                if (!modified)
                {
                    for (auto comp : this->m_components)
                    {
                        comp->setModified(false);
                    }
                }
                else
                {
                    for (auto output : this->m_outputList->getSlots())
                    {
                        for (auto input : output->getInputs())
                        {
                            input->getNode()->setModified(true);
                        }
                    }
                }
            }
        }
                
        auto Object::isModified() -> bool
        {
            return this->m_modified;
        }
                
        auto Object::setValid(bool valid) -> void
        {
            log_trace(Log::Set, valid);
            
            if (this->m_valid != valid)
            {
                this->m_valid = valid;
                emit this->validChanged();
            
                if (valid)
                {
                    Async::Synchronize([this]() {
                        for (auto entry : this->m_notifications)
                        {
                            entry->destroy();
                        }
                        
                        this->m_notifications.clear();
                        this->setErrorCount(0);
                    });
                }
            }
        }
            
        auto Object::setThreaded(bool threaded) -> void
        {
            log_trace(Log::Set, threaded);
            
            this->m_threaded = threaded;
            emit this->threadedChanged();
        }
 
        auto Object::getThreaded() -> bool
        {
            return this->m_threaded;
        }
                
        auto Object::setRunnable(bool runnable) -> void
        {
            log_trace(Log::Set, runnable);
            
            if (this->m_runnable != runnable)
            {
                this->m_runnable = runnable;
                emit this->runnableChanged();
            }
        }
            
        auto Object::isRunnable() -> bool
        {
            return this->m_runnable;
        }
            
        auto Object::getValid() -> bool
        {
            return this->m_valid;
        }
                        
        Object::~Object()
        {
            log_trace(Log::Del, this);
            
            if (PropertyController::instance->getNode() == this)
            {
                PropertyController::instance->reset();
            }

            if (Interface::Preview::Controller::instance->getNode() == this)
            {
                Interface::Preview::Controller::instance->reset();
            }
            
            for (auto entry : this->m_notifications)
            {
                entry->destroy();
            }

            this->m_outputList->deleteSlots();
            delete this->m_outputList;

            delete this->m_inputList;
            delete this->m_groupList;
            delete this->m_logic;
            
            Debug::Controller::instance->decNodeCount();
        }
    }
}