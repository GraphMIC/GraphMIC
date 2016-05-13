#include "gmConnectionObject.hpp"
#include "gmConnectionView.hpp"
#include "gmSlotInputBase.hpp"
#include "gmSlotOutputBase.hpp"
#include "gmNodeEditor.hpp"
#include "gmNodeGraph.hpp"
#include "gmNodeObject.hpp"

#include "gmDebugController.hpp"

namespace gm
{
    namespace Connection
    {
        Object::Object(Slot::OutputBase* out, Slot::InputBase* in) :
            m_output(out),
            m_input(in),
            m_hasData(true),
            m_view(nullptr),
            m_valid(false),
            m_offset(50)
        {
            m_input->setConnection(this);
            m_output->addConnection(this);
            
            Debug::Controller::instance->incConnectionCount();
        }
        
        auto Object::setView(View* view) -> void
        {
            this->m_view = view;
            
            if (!view)
            {
                return;
            }
            
            emit viewChanged();
            
            this->updateView();
            this->m_view->setHasData(this->m_hasData);
        }
        
        auto Object::updateView() -> void
        {
            if (!m_view)
            {
                return;
            }
            
            auto x1 = this->m_output->getX();
            auto y1 = this->m_output->getY();
            auto x2 = this->m_input->getX();
            auto y2 = this->m_input->getY();
            
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
            this->m_view->setX(x - m_offset);
            this->m_view->setY(y - m_offset);
            this->m_view->setWidth(w + m_offset * 2);
            this->m_view->setHeight(h + m_offset * 2);
            this->m_view->updatePath();
        }
        
        auto Object::getView() -> View*
        {
            return this->m_view;
        }
        
        auto Object::setValid(bool valid) -> void
        {
            if (this->m_valid != valid)
            {
                this->m_valid = valid;
                emit this->validChanged();
            }
        }
        
        auto Object::getValid() -> bool
        {
            return this->m_valid;
        }
        
        auto Object::setHasData(bool hasData) -> void
        {
            if (this->m_view)
            {
                this->m_view->setHasData(hasData);
            }
            
            this->m_hasData = hasData;
            emit this->hasDataChanged();
        }
        
        auto Object::getHasData() -> bool
        {
            return this->m_hasData;
        }
        
        auto Object::getOutput() -> Slot::OutputBase*
        {
            return this->m_output;
        }
        
        auto Object::getInput() -> Slot::InputBase*
        {
            return this->m_input;
        }

        auto Object::deleteObject() -> void
        {
            Delete(this);
        }
        
        Object::~Object()
        {
            this->m_input->removeConnection();
            this->m_output->removeConnection(this);
            
            Debug::Controller::instance->decConnectionCount();
        }
        
        auto Create(Slot::OutputBase* output, Slot::InputBase* input) -> void
        {
            auto connection = new Object(output, input);
            input->getNode()->getGraph()->addConnection(connection);
        }
        
        auto Delete(Connection::Object* connection) -> void
        {
            connection->getInput()->getNode()->getGraph()->deleteConnection(connection);
        }
    }
}