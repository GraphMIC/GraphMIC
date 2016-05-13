#include "gmPythonEditor.hpp"
#include "gmTextEditorController.hpp"

namespace gm
{
    namespace Python
    {
        Editor* Editor::instance = nullptr;
        
        Editor::Editor() : Base("Python")
        {
            log_trace(Log::New, this);
            
            this->m_textController = new TextEditor::Controller();
            
            if (instance)
            {
                throw "instance already existing";
            }
            
            instance        = this;
            this->m_script  = nullptr;
        }
        
        auto Editor::setScript(Script* script) -> void
        {
            log_trace(Log::Set);
            
            if (this->m_script != script)
            {
                if (this->m_script)
                {
                    emit this->saveScript();
                }
                
                this->m_script = script;
                emit this->scriptChanged();
            }
        }
        
        auto Editor::getScript() -> Script*
        {
            log_trace(Log::Get);
            
            return this->m_script;
        }
        
        auto Editor::getTextController() -> TextEditor::Controller*
        {
            log_trace(Log::Get);
            
            return this->m_textController;
        }
        
        auto Editor::Create() -> Editor*
        {
            log_trace(Log::Func);
            
            return new Editor();
        }
        
        auto Editor::onMenuAction(App::Menu::ActionID) -> void
        {
            log_trace(Log::Func);
        }
        
        Editor::~Editor()
        {
            log_trace(Log::Del);
        }
    }
}