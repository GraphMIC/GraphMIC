#include "gmPythonController.hpp"
#include "gmPythonEditor.hpp"
#include "gmPythonScriptList.hpp"
#include "gmPythonScript.hpp"
#include "gmPythonNodeDesigner.hpp"

#include "gmIOFile.hpp"
#include "gmIOPath.hpp"

#include "gmLog.hpp"

namespace gm
{
    namespace Python
    {
        Controller* Controller::instance = nullptr;
        
        Controller::Controller()
        {
            log_trace(Log::New);
            
            if (instance)
            {
                throw new std::runtime_error("instance already existing");
            }

            this->m_designer = Node::Designer::Create();
            
            this->m_scriptList  = new ScriptList();
            this->m_script      = nullptr;
            
            Editor::Create();
            
            instance = this;
        }
        
        auto Controller::Create() -> Controller*
        {
            log_trace(Log::Func);
            
            return new Controller();
        }

        auto Controller::getDesigner() -> Node::Designer*
        {
            return this->m_designer;
        }
        
        auto Controller::init() -> void
        {
            log_trace(Log::Func);
            
            auto script = new Script();
            script->setName("New Script");
            
            this->addScript(script);
        }
        
        auto Controller::addNewScript() -> void
        {
            log_trace(Log::Func);
            
            auto script = new Script();
            script->setName("New Script");
            
            this->addScript(script);
        }
        
        auto Controller::loadScript() -> void
        {
            log_trace(Log::Func);
            
            auto path = IO::File::SelectExistingFile("Load python script", "*.py");
            
            if (!path.isEmpty())
            {
                auto text = IO::File::Read(path);
                auto script = new Script();
                
                script->setText(text);
                script->setModified(false);
                script->setPath(path);
                script->setName(IO::Path::ExtractFileName(path));
                
                this->addScript(script);
            }
        }
        
        auto Controller::saveScript() -> void
        {
            log_trace(Log::Func);
            
            if (!this->m_script)
            {
                return;
            }
            
            auto path = this->m_script->getPath();
            
            if (!path.isEmpty())
            {
                IO::File::Write(path, getEditor()->getText());
                this->m_script->setModified(false);
            }
            else
            {
                this->saveScriptAs();
            }
        }
        
        auto Controller::saveScriptAs() -> void
        {
            log_trace(Log::Func);
            
            if (!this->m_script)
            {
                return;
            }

            auto suffix = this->m_script->isNodeScript() ? "*.pynode" : "*.py";
            auto dialogTitle = this->m_script->isNodeScript() ? "Save Python Node" : "Save Python Script";
            auto path = IO::File::SelectNewFile(dialogTitle, suffix);
            
            if (!path.isEmpty())
            {
                auto name = IO::Path::ExtractFileName(path);
                
                IO::File::Write(path, this->getEditor()->getText());
                
                this->m_script->setPath(path);
                this->m_script->setName(name);
                this->m_script->setModified(false);
            }
        }

        auto Controller::compileCurrentScript() -> void
        {
            if (!this->m_script)
            {
                return;
            }

            this->m_script->compile();
        }

        auto Controller::getEditor() -> Editor*
        {
            return Editor::instance;
        }
        
        auto Controller::getScriptList() -> ScriptList*
        {
            return this->m_scriptList;
        }
        
        auto Controller::getScript() -> Script*
        {
            return this->m_script;
        }
        
        auto Controller::setScript(Script* script) -> void
        {
            log_trace(Log::Set, script);
            
            if (this->m_script != script)
            {
                if (this->m_script)
                {
                    this->m_script->setText(Editor::instance->getText());
                    this->m_script->setActive(false);
                }
                
                this->m_script = script;
                Editor::instance->setScript(script);
                
                if (this->m_script)
                {
                    this->m_script->setActive(true);
                    Node::Designer::instance->setNode(this->m_script->getNode());
                }
                else
                {
                    Node::Designer::instance->setNode(nullptr);
                }
                
                emit this->scriptChanged();
            }
        }
        
        auto Controller::addScript(Script* script) -> void
        {
            log_trace(Log::Func);
            
            this->m_scriptList->addScript(script);
            this->setScript(script);
        }
        
        auto Controller::deleteScript(Script* script) -> void
        {
            log_trace(Log::Func, script);
            
            if (!script)
            {
                return;
            }
            
            if (this->m_script == script)
            {
                Script* newScript   = nullptr;
                auto scripts        = this->m_scriptList->getScripts();
                auto index          = scripts.indexOf(script);
                auto maxIndex       = scripts.count() - 1;
                auto newIndex       = std::min(index + 1, maxIndex);
                
                if (newIndex == index)
                {
                    if (newIndex < maxIndex)
                    {
                        ++newIndex;
                    }
                    else
                    {
                        --newIndex;
                    }
                }
                
                if (newIndex > -1)
                {
                    newScript = scripts.at(newIndex);
                }
                
                this->setScript(newScript);
            }
            
            this->m_scriptList->removeScript(script);
            delete script;
        }
        
        auto Controller::deleteCurrentScript() -> void
        {
            log_trace(Log::Func);
            
            if (this->m_script)
            {
                Node::Designer::instance->setNode(nullptr);
                this->deleteScript(this->m_script);
            }
        }
        
        Controller::~Controller()
        {
            log_trace(Log::Del, this);
        }
    }
}