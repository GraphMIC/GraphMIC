#include "gmLog.hpp"
#include "gmNodeEditor.hpp"
#include "gmNodeConnector.hpp"
#include "gmConnectionView.hpp"
#include "gmConnectionObject.hpp"
#include "gmDebugController.hpp"
#include "gmSlotOutputBase.hpp"

#include <QPainter>

namespace gm
{
    namespace Connection
    {
        View::View(QQuickItem* parent) : QQuickPaintedItem(parent), m_connector(nullptr), m_connection(nullptr)
        {
            this->setAntialiasing(true);
            
            this->m_color       = QColor("#aaa");
            this->m_offset      = 50;
            
            setAcceptedMouseButtons(Qt::AllButtons);
            
            Debug::Controller::instance->incConnectionViewCount();
        }
        
        auto View::setConnector(Node::Connector* connector) -> void
        {
            connector->setView(this);
        }
        
        auto View::getConnector() -> Node::Connector*
        {
            return this->m_connector;
        }
        
        auto View::mousePressEvent(QMouseEvent* evt) -> void
        {
            evt->setAccepted(false);
            
            if (!this->m_connection)
            {
                return;
            }
            
            auto x = evt->x();
            auto y = evt->y();
            auto sz = 4;
            
            m_selectionRect = QRect(QPoint(x-sz, y-sz), QPoint(x+sz, y+sz));
            
            if (m_path.intersects(m_selectionRect))
            {
                Node::Editor::instance->select(this->m_connection);
            }
            else
            {
                Node::Editor::instance->unselect(this->m_connection);
            }
            
            this->update();
        }
        
        auto View::setConnection(Object* connection) -> void
        {
            this->m_connection = connection;
            
            if (connection)
            {
                connection->setView(this);
                this->setHasData(connection->getHasData());
            }
            
            emit this->connectionChanged();
        }
        
        auto View::getConnection() -> Object*
        {
            return this->m_connection;
        }
        
        auto View::updatePath() -> void
        {
            this->m_path = QPainterPath();
            
            auto w      = width();
            auto h      = height();
            auto start  = QPoint(m_offset, h - m_offset);
            auto end    = QPoint(w - m_offset, m_offset);
            
            if (this->m_quadrant == 2 || this->m_quadrant == 8)
            {
                start.setY(m_offset);
                end.setY(h - m_offset);
            }
            
            auto m      = QPoint(w/2, h/2);
            
            auto c1     = QPoint(m_offset + m_offset, start.y());
            auto c2     = QPoint(end.x() - m_offset, end.y());
            
            if (this->m_quadrant == 2 || this->m_quadrant == 4)
            {
                c1 -= QPoint(m_offset * 2, 0);
                c2 += QPoint(m_offset * 2, 0);
            }
            
            this->m_path.moveTo(start);
            this->m_path.quadTo(c1, m);
            this->m_path.quadTo(c2, end);
        }
        
        auto View::setHasData(bool hasData) -> void
        {/*
            Dispatch::onMain([this, hasData](){
                this->m_hasData = hasData;
                
                if (hasData)
                {
                    this->m_color = QColor("#ff00ff");
                }
                else
                {
                    this->m_color = QColor("#00ff00");
                }
                
                this->update();
            });*/
        }
        
        auto View::paint(QPainter* painter) -> void
        {
            if (this->m_connection)
            {
                this->m_color = QColor("#fff");
            } else {
                this->m_color = QColor("#939CAA");
            }

            painter->setPen(QPen(this->m_color, 1.5));
            painter->drawPath(this->m_path);
        }
        
        auto View::setQuadrant(int quadrant) -> void
        {
            this->m_quadrant = quadrant;
        }

        View::~View()
        {
            if (this->m_connection)
            {
                this->m_connection->setView(nullptr);
            }
            
            if (this->m_connector)
            {
                this->m_connector->setView(nullptr);
            }
            
            Debug::Controller::instance->decConnectionViewCount();
        }
    }
}
