#include "gmPythonNodeObject.hpp"
#include "gmPythonNodeParam.hpp"
#include "gmPythonNodeOutput.hpp"
#include "gmPythonNodeInput.hpp"
#include "gmPythonNodeNumber.hpp"
#include "gmPythonNodeString.hpp"
#include "gmPythonNodeOption.hpp"
#include "gmPythonNodeBool.hpp"
#include "gmPythonNodeVector.hpp"
#include "gmPythonNodeDir.hpp"
#include "gmPythonNodeFiles.hpp"
#include "gmPythonLogic.hpp"
#include "gmPythonScript.hpp"
#include "gmPythonController.hpp"

#include "gmNodeSearch.hpp"
#include "gmLogicFactory.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            Object::Object(Script* script): m_script(script)
            {
                log_trace(Log::New);

                this->m_name = "python node";
                this->m_author = "author";
                this->m_docLink = "http://www.example.com";
                this->m_versionMajor = 1;
                this->m_versionMinor = 0;
                this->m_versionPatch = 0;
                this->m_runnable = true;
                this->m_forceExecution = true;
            }

            auto Object::getScript() -> Script*
            {
                return this->m_script;
            }

            auto Object::setDocLink(const QString& docLink) -> void
            {
                this->m_docLink = docLink;
                emit this->docLinkChanged();
            }

            auto Object::getDocLink() -> QString
            {
                return this->m_docLink;
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
            
            auto Object::setRunnable(bool runnable) -> void
            {
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
            
            auto Object::setAuthor(const QString& author) -> void
            {
                this->m_author = author;
                emit this->authorChanged();
            }

            auto Object::getAuthor() -> QString
            {
                return this->m_author;
            }

            auto Object::setName(const QString& name) -> void
            {
                this->m_name = name;
                emit this->nameChanged();
            }

            auto Object::getName() -> QString
            {
                return this->m_name;
            }

            auto Object::setVersionMajor(int versionMajor) -> void
            {
                if (this->m_versionMajor != versionMajor)
                {
                    this->m_versionMajor = versionMajor;
                    emit this->versionMajorChanged();
                }
            }

            auto Object::getVersionMajor() -> int
            {
                return this->m_versionMajor;
            }

            auto Object::setVersionMinor(int versionMinor) -> void
            {
                if (this->m_versionMinor != versionMinor)
                {
                    this->m_versionMinor = versionMinor;
                    emit this->versionMinorChanged();
                }
            }

            auto Object::getVersionMinor() -> int
            {
                return this->m_versionMinor;
            }

            auto Object::setVersionPatch(int versionPatch) -> void
            {
                if (this->m_versionPatch != versionPatch)
                {
                    this->m_versionPatch = versionPatch;
                    emit this->versionPatchChanged();
                }
            }

            auto Object::getVersionPatch() -> int
            {
                return this->m_versionPatch;
            }

            auto Object::clearSelection() -> void
            {
                this->setSelected(nullptr);
            }

            auto Object::setSelected(Component* component) -> void
            {
                if (this->m_selected != component)
                {
                    if (this->m_selected)
                    {
                        this->m_selected->setSelected(false);
                    }

                    this->m_selected = component;
                    emit this->selectedChanged();
                }
            }

            auto Object::getSelected() -> Component*
            {
                return this->m_selected;
            }
            
            auto Object::getInputList() -> QQmlListProperty<Input>
            {
                return QQmlListProperty<Input>(this, this->m_inputs);
            }

            auto Object::getOutputList() -> QQmlListProperty<Output>
            {
                return QQmlListProperty<Output>(this, this->m_outputs);
            }

            auto Object::getParamList() -> QQmlListProperty<Param>
            {
                return QQmlListProperty<Param>(this, this->m_params);
            }

            auto Object::addInput() -> void
            {
                auto component = new Input(this);

                this->m_inputs.append(component);
                emit this->inputsChanged();

                component->select();
            }

            auto Object::addOutput() -> void
            {
                auto component = new Output(this);

                this->m_outputs.append(component);
                emit this->outputsChanged();

                component->select();
            }

            auto Object::addNumberParam() -> void
            {
                auto component = new Number(this);

                this->m_params.append(component);
                emit this->paramsChanged();

                component->select();
            }

            auto Object::addVectorParam() -> void
            {
                auto component = new Vector(this);

                this->m_params.append(component);
                emit this->paramsChanged();

                component->select();
            }

            auto Object::addStringParam() -> void
            {
                auto component = new String(this);

                this->m_params.append(component);
                emit this->paramsChanged();

                component->select();
            }

            auto Object::addBoolParam() -> void
            {
                auto component = new Bool(this);

                this->m_params.append(component);
                emit this->paramsChanged();

                component->select();
            }

            auto Object::addDirParam() -> void
            {
                auto component = new Dir(this);

                this->m_params.append(component);
                emit this->paramsChanged();

                component->select();
            }

            auto Object::addOptionParam() -> void
            {
                auto component = new Option(this);

                this->m_params.append(component);
                emit this->paramsChanged();

                component->select();
            }

            auto Object::addFilesParam() -> void
            {
                auto component = new Files(this);

                this->m_params.append(component);
                emit this->paramsChanged();

                component->select();
            }

            auto Object::deleteInput(Input* input) -> void
            {
                this->m_inputs.removeOne(input);
                emit this->inputsChanged();

                if (input == this->m_selected)
                {
                    this->setSelected(nullptr);
                }

                delete input;
            }

            auto Object::deleteOutput(Output* output) -> void
            {
                this->m_outputs.removeOne(output);
                emit this->outputsChanged();

                if (output == this->m_selected)
                {
                    this->setSelected(nullptr);
                }

                delete output;
            }

            auto Object::getInputs() -> QList<Input*>
            {
                return this->m_inputs;
            }

            auto Object::getOutputs() -> QList<Output*>
            {
                return this->m_outputs;
            }

            auto Object::getParams() -> QList<Param*>
            {
                return this->m_params;
            }

            auto Object::create() -> void
            {
                emit Controller::instance->updateScript();

                auto identifier = "python::" + this->m_name;

                log_trace(Log::Func, identifier.toStdString());

                if (!gm::Node::Search::instance->contains(identifier))
                {
                    gm::Node::Search::instance->AddEntry(identifier);
                    gm::Node::Search::instance->updateMatches();
                }

                auto node = this;

                gm::Logic::Factory::RegisterCustomLogic(identifier, [node](){
                    return new Logic(node);
                });
            }

            auto Object::deleteParam(Param* param) -> void
            {
                this->m_params.removeOne(param);
                emit this->paramsChanged();

                if (param == this->m_selected)
                {
                    this->setSelected(nullptr);
                }

                delete param;
            }
        }
    }
}
