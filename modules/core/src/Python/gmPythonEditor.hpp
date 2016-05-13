#pragma once

#include "gmAppContextBase.hpp"

namespace gm
{
    namespace TextEditor
    {
        class Controller;
    }
    
    namespace Python
    {
        class Script;
        
        class Editor : public App::Context::Base
        {
            Q_OBJECT
            Q_PROPERTY(gm::Python::Script* script READ getScript NOTIFY scriptChanged);
            Q_PROPERTY(gm::TextEditor::Controller* textController READ getTextController CONSTANT);
        private:
            Script* m_script;
            TextEditor::Controller* m_textController;
            Editor();
        public:
            static Editor* instance;
            auto onMenuAction(App::Menu::ActionID) -> void override;
            auto getTextController() -> TextEditor::Controller*;
            auto setScript(Script*) -> void;
            auto getScript() -> Script*;
            static auto Create() -> Editor*;
            ~Editor();
        signals:
            void scriptChanged();
            void saveScript();
        };
    }
}
