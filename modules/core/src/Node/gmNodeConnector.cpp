#include "gmLog.hpp"
#include "gmNodeConnector.hpp"
#include "gmConnectionView.hpp"

namespace gm
{
    namespace Node
    {
        Connector* Connector::instance = nullptr;
        
        Connector::Connector() : m_view(nullptr)
        {
            log_trace(Log::New, this);
            
            if (instance)
            {
                throw "instance already existing";
            }
            
            instance = this;
        }
        
        auto Connector::updateView() -> void
        {
            if (!m_view)
            {
                return;
            }
            
            auto x1 = this->m_x1;
            auto y1 = this->m_y1;
            auto x2 = this->m_x2;
            auto y2 = this->m_y2;
            
            auto x = 0;
            auto y = 0;
            auto w = 0;
            auto h = 0;
            
            auto q = 0;
            
            if (x2 > x1)
            {
                x = x1;
                w = x2 - x1;
                q |= 9;
            }
            else
            {
                x = x2;
                w = x1 - x2;
                q |= 6;
            }
            if (y2 > y1)
            {
                y = y1;
                h = y2 - y1;
                q &= 12;
            }
            else
            {
                y = y2;
                h = y1 - y2;
                q &= 3;
            }
            
            this->m_view->setQuadrant(q);
            this->m_view->setX(x - 50);
            this->m_view->setY(y - 50);
            this->m_view->setWidth(w + 50 * 2);
            this->m_view->setHeight(h + 50 * 2);
            this->m_view->updatePath();
        }
        
        auto Connector::setView(Connection::View* view) -> void
        {
            this->m_view = view;
            
            if (view)
            {
                view->setX(100);
                view->setY(100);
                view->setWidth(400);
                view->setHeight(400);
                view->updatePath();
            }
        }
        
        auto Connector::getView() -> Connection::View*
        {
            return this->m_view;
        }
        
        auto Connector::setActive(bool active) -> void
        {
            log_trace(Log::Set, active);
            
            if (this->m_active != active)
            {
                this->m_active = active;
                emit this->activeChanged();
                
                if (this->m_view)
                {
                    this->m_view->setVisible(active);
                }
            }
        }
        
        auto Connector::setX1(int x1) -> void
        {
            if (this->m_x1 != x1)
            {
                this->m_x1 = x1;
                emit this->x1Changed();
                
                updateView();
            }
        }
        
        auto Connector::getX1() -> int
        {
            return this->m_x1;
        }
        
        auto Connector::setY1(int y1) -> void
        {
            if (this->m_y1 != y1)
            {
                this->m_y1 = y1;
                emit this->y1Changed();
                
                updateView();
            }
        }
        
        auto Connector::getY1() -> int
        {
            return this->m_y1;
        }
        
        auto Connector::setX2(int x2) -> void
        {
            if (this->m_x2 != x2)
            {
                this->m_x2 = x2;
                emit this->x2Changed();
                
                updateView();
            }
        }
        
        auto Connector::getX2() -> int
        {
            return this->m_x2;
        }
        
        auto Connector::setY2(int y2) -> void
        {
            if (this->m_y2 != y2)
            {
                this->m_y2 = y2;
                emit this->y2Changed();
                
                updateView();
            }
        }
        
        auto Connector::getY2() -> int
        {
            return this->m_y2;
        }
        
        auto Connector::getActive() -> bool
        {
            log_trace(Log::Get);
            
            return this->m_active;
        }
        
        Connector::~Connector()
        {
            log_trace(Log::Del, this);
        }
    }
}
