#pragma once

#include "gmCoreExport.hpp"

#include <QPoint>
#include <QObject>

namespace gm
{
    namespace Connection
    {
        class List;
        class Object;
    }
    
    namespace Node
    {
        class Object;
        class List;
        class Selectable;
        
        class GM_CORE_EXPORT Graph : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QPoint position READ getPosition);
            Q_PROPERTY(gm::Node::List* nodeList READ getNodeList CONSTANT);
            Q_PROPERTY(gm::Connection::List* connectionList READ getConnectionList CONSTANT);
            Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
            Q_PROPERTY(QString path READ getPath NOTIFY pathChanged);
            Q_PROPERTY(int selectionCount READ getSelectionCount NOTIFY selectionCountChanged);
            Q_PROPERTY(bool active READ getActive NOTIFY activeChanged);
            Q_PROPERTY(bool modified READ isModified NOTIFY modifiedChanged);
        private:
            friend class Editor;
            Node::List* m_nodeList;
            Connection::List* m_connectionList;
            QList<Selectable*> m_selection;
            QPoint m_position;
            QString m_path;
            QString m_name;
            bool m_modified;
            bool m_active;
            int m_selectionCount;
            int m_maxLayer;
        public:
            static const int MaxNodeCount;
        private:
            auto getNodeList() -> Node::List*;
            auto getConnectionList() -> Connection::List*;
            auto deleteSelection() -> void;
            auto setActive(bool) -> void;
            auto getActive() -> bool;
            auto addSelection(Selectable*) -> void;
            auto removeSelection(Selectable*) -> void;
            auto setSelection(Selectable*) -> void;
            auto clearSelection() -> void;
            auto setSelectionCount(int) -> void;
            auto sortNodeLayers() -> void;
        public:
            Graph();
            auto setName(const QString&) -> void;
            auto getName() -> QString;
            auto setPath(const QString&) -> void;
            auto getPath() -> QString;
            auto getNodes() -> QList<Node::Object*>;
            auto getConnections() -> QList<Connection::Object*>;
            auto addNode(Object*) -> void;
            auto deleteNode(Object*) -> void;
            auto removeNode(Object*) -> void;
            auto addConnection(Connection::Object*) -> void;
            auto deleteConnection(Connection::Object*) -> void;
            auto raiseNode(Object*) -> void;
            auto setModified(bool) -> void;
            auto isModified() -> bool;
            auto getPosition() -> QPoint;
            auto getSelectionCount() -> int;
            auto getNodeCount() -> int;
            ~Graph();
        public slots:
            void setPosition(int, int);
            void remove();
            void activate();
            void execute();
        signals:
            void selectionCountChanged();
            void modifiedChanged();
            void activeChanged();
            void pathChanged();
            void nameChanged();
        };
    }
}
