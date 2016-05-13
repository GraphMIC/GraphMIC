#pragma once

#include <QObject>

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class Object;
        }

        class Script : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(gm::Python::Node::Object* node READ getNode CONSTANT);
            Q_PROPERTY(QString path READ getPath WRITE setPath NOTIFY pathChanged);
            Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
            Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged);
            Q_PROPERTY(QString output READ getOutput WRITE setOutput NOTIFY outputChanged);
            Q_PROPERTY(bool nodeScript READ isNodeScript WRITE setNodeScript NOTIFY nodeScriptChanged);
            Q_PROPERTY(bool active READ getActive NOTIFY activeChanged);
            Q_PROPERTY(bool modified READ isModified NOTIFY modifiedChanged);
        private:
            Node::Object* m_node;
            QString m_path;
            QString m_name;
            QString m_text;
            bool m_nodeScript;
            QString m_output;
            bool m_modified;
            bool m_active;
        public:
            Script();
            auto setModified(bool) -> void;
            auto isModified() -> bool;
            auto setNodeScript(bool) -> void;
            auto isNodeScript() -> bool;
            auto getNode() -> Node::Object*;
            auto setName(const QString&) -> void;
            auto getName() -> QString;
            auto setPath(const QString&) -> void;
            auto getPath() -> QString;
            auto setText(const QString&) -> void;
            auto getText() -> QString;
            auto setActive(bool) -> void;
            auto getActive() -> bool;
            auto setOutput(const QString&) -> void;
            auto getOutput() -> QString;
            auto updateScript() -> void;
            ~Script();
        public slots:
            void activate();
            void remove();
            void compile();
        signals:
            void nodeScriptChanged();
            void modifiedChanged();
            void activeChanged();
            void pathChanged();
            void nameChanged();
            void textChanged();
            void outputChanged();
        };
    }
}
