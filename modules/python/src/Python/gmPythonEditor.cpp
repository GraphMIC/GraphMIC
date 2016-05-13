#include <boost/python.hpp>
#include "gmPythonEditor.hpp"

#include "gmLog.hpp"
#include "gmApp.hpp"
#include "gmPythonScript.hpp"
#include "gmPythonController.hpp"
#include "gmPythonHighlighter.hpp"

#include <QClipboard>
#include <QTextOption>
#include <QTextCursor>
#include <QRegularExpression>

namespace gm
{
    namespace Python
    {
        Editor* Editor::instance = nullptr;
        
        Editor::Editor()
        {
            log_trace(Log::New);
            
            if (instance)
            {
                throw new std::runtime_error("instance already existing");
            }
            
            this->m_highlighter     = nullptr;
            this->m_script          = nullptr;
            this->m_selectionStart  = 0;
            this->m_selectionEnd    = 0;
            this->m_editorCursor    = 0;
            this->m_line            = 0;
            this->m_column          = 0;
            this->m_fontSize        = 12;
            
            instance = this;
        }
        
        auto Editor::Create() -> void
        {
            new Editor();
        }
        
        auto Editor::setScript(Script* script) -> void
        {
            log_trace(Log::Set, script);
            
            this->m_script = script;
        }
        
        auto Editor::getScript() -> Script*
        {
            return this->m_script;
        }
            
        auto Editor::setText(const QString& text) -> void
        {
            log_trace(Log::Set);
            
            this->m_document->textDocument()->setPlainText(text);
        }
        
        auto Editor::getText() -> QString
        {
            return this->m_document->textDocument()->toPlainText();
        }
        
        auto Editor::setDocument(QQuickTextDocument* document) -> void
        {
            log_trace(Log::Set);
            
            this->m_document = document;
            this->m_document->textDocument()->setIndentWidth(2);
            
            auto options = this->m_document->textDocument()->defaultTextOption();
            options.setTabStop(20);
            options.setFlags(QTextOption::ShowTabsAndSpaces | QTextOption::ShowLineAndParagraphSeparators);
            this->m_document->textDocument()->setDefaultTextOption(options);
            
            emit this->documentChanged();
            
            this->m_highlighter = new Highlighter(this);
        }
        
        auto Editor::setLine(int line) -> void
        {
            if (this->m_line != line)
            {
                this->m_line = line;
                emit this->lineChanged();
            }
        }
        
        auto Editor::getLine() -> int
        {
            return this->m_line;
        }
        
        auto Editor::setColumn(int column) -> void
        {
            if (this->m_column != column)
            {
                this->m_column = column;
                emit this->columnChanged();
            }
        }
        
        auto Editor::getColumn() -> int
        {
            return this->m_column;
        }
        
        auto Editor::setSelectionStart(int pos) -> void
        {
            log_trace(Log::Set);
            
            this->m_selectionStart = pos;
            
            emit this->selectionStartChanged();
            
            auto cursor = getCurrentCursor();
            cursor.setPosition(pos);
            this->setLine(cursor.blockNumber());
            this->setColumn(cursor.columnNumber());
        }
        
        auto Editor::setSelectionEnd(int pos) -> void
        {
            log_trace(Log::Set);
            
            this->m_selectionEnd = pos;
            
            emit this->selectionEndChanged();
        }
        
        auto Editor::getDocument() -> QQuickTextDocument*
        {
            return this->m_document;
        }
        
        auto Editor::getSelectionStart() -> int
        {
            log_trace(Log::Get);
            
            return this->m_selectionStart;
        }
        
        auto Editor::getSelectionEnd() -> int
        {
            log_trace(Log::Get);
            
            return this->m_selectionEnd;
        }
        
        auto Editor::getCurrentCursor() -> QTextCursor
        {
            log_trace(Log::Get);
            
            auto c = QTextCursor(this->m_document->textDocument());
            
            c.setPosition(this->m_selectionEnd, QTextCursor::MoveAnchor);
            c.setPosition(this->m_selectionStart, QTextCursor::KeepAnchor);
            
            return c;
        }
        
        auto Editor::setEditorCursor(int position) -> void
        {
            log_trace(Log::Set);
            
            this->m_editorCursor = position;
            
            emit this->editorCursorChanged();
        }
        
        auto Editor::getEditorCursor() -> int
        {
            log_trace(Log::Get);
            
            return this->m_editorCursor;
        }
        
        auto Editor::setFontSize(int fontSize) -> void
        {
            this->m_fontSize = fontSize;
            emit this->fontSizeChanged();
        }
        
        auto Editor::getFontSize() -> int
        {
            return this->m_fontSize;
        }
        
        auto Editor::invalidateScript() -> void
        {
            if (this->m_script)
            {
                this->m_script->setModified(true);
            }
        }
        
        auto Editor::onKeyPressed(int key, int modifiers, QString string) -> bool
        {
            if (!this->m_script)
            {
                if (modifiers == Qt::ControlModifier)
                {
                    if (key == Qt::Key_O)
                    {
                        Python::Controller::instance->loadScript();
                    }
                    else if (key == Qt::Key_N || key == Qt::Key_T)
                    {
                        Python::Controller::instance->addNewScript();
                    }
                    else if (key == Qt::Key_W)
                    {
                        Python::Controller::instance->deleteCurrentScript();
                    }
                }
                
                return true;
            }
            
            if (modifiers == Qt::ControlModifier)
            {
                if (key == Qt::Key_Plus)
                {
                    this->setFontSize(this->m_fontSize + 2);
                    return true;
                }
                if (key == Qt::Key_Minus)
                {
                    this->setFontSize(this->m_fontSize - 2);
                    return true;
                }
                if (key == Qt::Key_S)
                {
                    Python::Controller::instance->saveScript();
                    return true;
                }
                if (key == Qt::Key_R)
                {
                    Python::Controller::instance->compileCurrentScript();
                    return true;
                }
                if (key == Qt::Key_O)
                {
                    Python::Controller::instance->loadScript();
                    return true;
                }
                if (key == Qt::Key_N)
                {
                    Python::Controller::instance->addNewScript();
                    return true;
                }
                if (key == Qt::Key_W)
                {
                    Python::Controller::instance->deleteCurrentScript();
                    return true;
                }
                if (key == Qt::Key_V)
                {
                    auto text = Application::getClipboard()->text();
                    
                    if (!text.isEmpty())
                    {
                        auto cursor = this->getCurrentCursor();
                        cursor.beginEditBlock();
                        cursor.insertText(text);
                        cursor.endEditBlock();
                        
                        this->invalidateScript();
                    }
                    return true;
                }
            }
            
            if (QRegularExpression("(\\w+)|(\\W+)").match(string).hasMatch())
            {
                this->invalidateScript();
            }
            
            return false;
        }
        
        Editor::~Editor()
        {
            log_trace(Log::Del, this);
        }
    }
}