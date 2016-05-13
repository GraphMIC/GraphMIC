#pragma once

#include "gmInterfacePythonController.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class Designer;
        }

        class Editor;
        class Script;
        class ScriptList;
        
        class Controller : public Interface::Python::Controller
        {
            Q_OBJECT
            Q_PROPERTY(gm::Python::Node::Designer* designer READ getDesigner CONSTANT);
            Q_PROPERTY(gm::Python::Editor* editor READ getEditor CONSTANT);
            Q_PROPERTY(gm::Python::ScriptList* scriptList READ getScriptList CONSTANT);
            Q_PROPERTY(gm::Python::Script* script READ getScript NOTIFY scriptChanged);
        private:
            Node::Designer* m_designer;
            ScriptList* m_scriptList;
            Script* m_script;
        public:
            static Controller* instance;
        public:
            Controller();
            auto init() -> void;
            auto getDesigner() -> Node::Designer*;
            auto getScriptList() -> ScriptList*;
            auto getScript() -> Script*;
            auto getEditor() -> Editor*;
            auto setScript(Script*) -> void;
            auto addScript(Script*) -> void;
            auto deleteScript(Script*) -> void;
            auto deleteCurrentScript() -> void;
            auto compileCurrentScript() -> void;
            static auto Create() -> Controller*;
            ~Controller();
        public slots:
            void addNewScript();
            void loadScript();
            void saveScript();
            void saveScriptAs();
        signals:
            void scriptChanged();
            void updateScript();
        };
    }
}
