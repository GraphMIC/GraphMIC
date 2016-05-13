#pragma once

#include <QSyntaxHighlighter>
#include <QString>

namespace gm
{
    namespace Python
    {
        class Editor;
        
        class Highlighter : public QSyntaxHighlighter
        {
        private:
            struct Rule
            {
                QRegExp pattern;
                QTextCharFormat format;
            };
        private:
            QList<Rule> m_rules;
            Editor* m_editor;
            QTextDocument* m_doc;
        private:
            auto init() -> void;
        public:
            Highlighter() = delete;
            Highlighter(Editor* editor);
            auto highlightBlock(const QString &text) -> void override;
            ~Highlighter();
        };
    }
}
