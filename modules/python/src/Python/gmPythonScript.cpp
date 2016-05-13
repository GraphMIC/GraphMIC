#include <boost/python.hpp>

#include "gmPythonScript.hpp"
#include "gmPythonController.hpp"
#include "gmPythonNodeObject.hpp"

#include "gmLog.hpp"
#include "gmApp.hpp"
#include "gmPythonService.hpp"

namespace gm
{
    namespace Python
    {
        Script::Script() : m_modified(true)
        {
            log_trace(Log::New, this);

            this->m_node = new Node::Object(this);
            this->m_nodeScript = false;
        }

        auto Script::setNodeScript(bool nodeScript) -> void
        {
            if (this->m_nodeScript != nodeScript)
            {
                this->m_nodeScript = nodeScript;
                emit this->nodeScriptChanged();
            }
        }

        auto Script::isNodeScript() -> bool
        {
            return this->m_nodeScript;
        }

        auto Script::setModified(bool modified) -> void
        {
            log_trace(Log::Set, modified);

            if (this->m_modified != modified)
            {
                this->m_modified = modified;
                emit this->modifiedChanged();
            }
        }

        auto Script::isModified() -> bool
        {
            return this->m_modified;
        }

        auto Script::setPath(const QString& path) -> void
        {
            log_trace(Log::Set, path.toStdString());

            this->m_path = path;
            emit this->pathChanged();
        }

        auto Script::getPath() -> QString
        {
            log_trace(Log::Get);

            return this->m_path;
        }

        auto Script::setName(const QString& name) -> void
        {
            log_trace(Log::Set);

            this->m_name = name;
            emit this->nameChanged();
        }

        auto Script::getName() -> QString
        {
            return this->m_name;
        }

        auto Script::setText(const QString& text) -> void
        {
            log_trace(Log::Set);

            this->m_text = text;
            emit this->textChanged();
        }

        auto Script::getText() -> QString
        {
            return this->m_text;
        }

        auto Script::setActive(bool active) -> void
        {
            log_trace(Log::Set, active);

            if (this->m_active != active)
            {
                this->m_active = active;
                emit this->activeChanged();
            }
        }

        auto Script::getActive() -> bool
        {
            return this->m_active;
        }

        auto Script::getOutput() -> QString
        {
            return this->m_output;
        }

        auto Script::setOutput(const QString& output) -> void
        {
            log_trace(Log::Set);

            this->m_output = output;
            emit this->outputChanged();
        }

        auto Script::updateScript() -> void
        {
            emit Controller::instance->updateScript();
        }

        auto Script::compile() -> void
        {
            this->setOutput("");
            this->updateScript();

            log_trace(Log::Func);

            /****TEST****/
            using namespace boost::python;
            PyThreadState*  state;
            std::string     stream;
            try
            {
                state   = Service::instance->startThreadedInterpreter();
                stream  = Service::instance->runSimpleString(this->getText().toStdString());

                this->setOutput(QString::fromStdString(stream));
                Service::instance->stopThreadedInterpreter(state);
            }
            catch( error_already_set )
            {
                QString erroMessage = QString::fromStdString(Service::instance->parsePythonException()).toHtmlEscaped();

                erroMessage.push_front("<b><FONT COLOR='#ff0000'>");
                erroMessage.push_back("</b></br>");
                this->setOutput(erroMessage);
                Service::instance->stopThreadedInterpreter(state);
            }

            log_trace(Log::Func);
        }

        auto Script::activate() -> void
        {
            log_trace(Log::Func);

            Controller::instance->setScript(this);
        }

        auto Script::remove() -> void
        {
            log_trace(Log::Func);

            Controller::instance->deleteScript(this);
        }

        auto Script::getNode() -> Node::Object*
        {
            return this->m_node;
        }

        Script::~Script()
        {
            log_trace(Log::Del, this);

            delete this->m_node;
            this->m_node = nullptr;
        }
    }
}
