#pragma once

#include <QQuickPaintedItem>
#include <QPainterPath>

namespace gm
{
    namespace Node
    {
        class Connector;
    }
    
    namespace Connection
    {
        class Object;
        
        class View : public QQuickPaintedItem
        {
            Q_OBJECT
            Q_PROPERTY(gm::Connection::Object* connection READ getConnection WRITE setConnection NOTIFY connectionChanged);
            Q_PROPERTY(gm::Node::Connector* connector READ getConnector WRITE setConnector NOTIFY connectorChanged);
        private:
            Node::Connector* m_connector;
            QPainterPath m_path;
            QRect m_selectionRect;
            Object* m_connection;
            QColor m_color;
            bool m_hasData;
            int m_quadrant;
            int m_offset;
        public:
            View(QQuickItem* = 0);
            auto setConnector(Node::Connector*) -> void;
            auto getConnector() -> Node::Connector*;
            auto setConnection(Object*) -> void;
            auto getConnection() -> Object*;
            auto setHasData(bool) -> void;
            auto setQuadrant(int) -> void;
            auto updatePath() -> void;
            auto paint(QPainter*) -> void override;
            auto mousePressEvent(QMouseEvent*) -> void override;
            ~View();
        signals:
            void connectionChanged();
            void connectorChanged();
        };
    }
}
