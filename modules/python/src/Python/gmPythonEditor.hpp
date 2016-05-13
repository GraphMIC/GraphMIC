#pragma once
#include "gmPythonExport.hpp"

#include <QObject>
#include <QQuickTextDocument>

namespace gm
{
    namespace Python
    {
        class Highlighter;
        class Script;
        
        class GM_PYTHON_EXPORT Editor : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QQuickTextDocument* document READ getDocument WRITE setDocument NOTIFY documentChanged);
            Q_PROPERTY(int selectionStart READ getSelectionStart WRITE setSelectionStart NOTIFY selectionStartChanged);
            Q_PROPERTY(int selectionEnd READ getSelectionEnd WRITE setSelectionEnd NOTIFY selectionEndChanged);
            Q_PROPERTY(int editorCursor READ getEditorCursor WRITE setEditorCursor NOTIFY editorCursorChanged);
            Q_PROPERTY(int fontSize READ getFontSize NOTIFY fontSizeChanged);
            Q_PROPERTY(int line READ getLine NOTIFY lineChanged);
            Q_PROPERTY(int column READ getColumn NOTIFY columnChanged);
        private:
            friend class Highlighter;
            QQuickTextDocument* m_document;
            Highlighter* m_highlighter;
            Script* m_script;
            int m_selectionStart;
            int m_selectionEnd;
            int m_editorCursor;
            int m_fontSize;
            int m_column;
            int m_line;
        public:
            static Editor* instance;
            Editor();
            static auto Create() -> void;
            auto init() -> void;
            auto setDocument(QQuickTextDocument* document) -> void;
            auto getDocument() -> QQuickTextDocument*;
            auto setScript(Script*) -> void;
            auto getScript() -> Script*;
            auto getText() -> QString;
            auto setText(const QString&) -> void;
            auto setLine(int) -> void;
            auto getLine() -> int;
            auto setColumn(int) -> void;
            auto getColumn() -> int;
            auto setSelectionStart(int pos) -> void;
            auto setSelectionEnd(int pos) -> void;
            auto getSelectionStart() -> int;
            auto getSelectionEnd() -> int;
            auto setEditorCursor(int position) -> void;
            auto getEditorCursor() -> int;
            auto getCurrentCursor() -> QTextCursor;
            auto setFontSize(int) -> void;
            auto getFontSize() -> int;
            auto invalidateScript() -> void;
            ~Editor();
        public slots:
            bool onKeyPressed(int key, int modifiers, QString string);
        signals:
            void selectionStartChanged();
            void editorCursorChanged();
            void selectionEndChanged();
            void fontSizeChanged();
            void documentChanged();
            void columnChanged();
            void lineChanged();
        };
    }
}