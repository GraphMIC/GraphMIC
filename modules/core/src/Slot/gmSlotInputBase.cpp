#include "gmSlotInputBase.hpp"
#include "gmSlotInput.hpp"

#include "gmDataBase.hpp"
#include "gmDataImage.hpp"

#include "gmConnectionObject.hpp"
#include "gmSlotConstraints.hpp"

#include "gmAsync.hpp"

#include <QJsonObject>

namespace gm
{
    namespace Slot
    {
        Component::Type InputBase::ComponentType = Component::Type::Input;
        
        InputBase::InputBase(const QString& name,
                             Data::Type dataType,
                             Data::Connection dataConnection,
                             Slot::Constraints* imageConstraints
                             ) :
            Base(ComponentType, dataType, name, imageConstraints),
            m_dataConnection(dataConnection),
            m_connection(nullptr)
        {
            log_trace(Log::New, this);
        }

        auto InputBase::getMockData() -> QList<Data::Base*>
        {
            return this->m_mockData;
        }

        auto InputBase::addMockData(Data::Base* data) -> void
        {
            log_trace(Log::Func);

            if (data->getDataType() != this->getDataType())
            {
                throw new std::runtime_error("slot type and data type are not compatible. i will die now.");
            }

            if (this->getConstraints()->accept(data))
            {
                this->m_mockData.append(data);
            }
        }

        auto InputBase::clearMockData() -> void
        {
            log_trace(Log::Func);

            this->m_mockData.clear();
        }
        
        auto InputBase::onPositionChanged() -> void
        {
            if (this->m_connection)
            {
                this->m_connection->updateView();
            }
        }

        auto InputBase::isRequired() -> bool
        {
            return this->m_dataConnection == Data::Connection::Required;
        }

        auto InputBase::getOutput() -> OutputBase*
        {
            return this->m_connection ? this->m_connection->getOutput() : nullptr;
        }

        auto InputBase::isConnected(OutputBase* output) -> bool
        {
            return this->m_connection ? this->m_connection->getOutput() == output : false;
        }
        
        auto InputBase::isConnected() -> bool
        {
            return this->m_connection || this->m_mockData.count();
        }
        
        auto InputBase::setConnection(Connection::Object* connection) -> void
        {
            log_trace(Log::Set);
            
            if (this->m_connection)
            {
                Connection::Delete(this->m_connection);
            }
            
            this->m_connection = connection;
            emit this->outputChanged();
        }
        
        auto InputBase::removeConnection() -> void
        {
            log_trace(Log::Func);
            
            this->m_connection = nullptr;
            emit this->outputChanged();
        }

        auto InputBase::disconnect() -> void
        {
            log_trace(Log::Func);

            if (this->m_connection)
            {
                Connection::Delete(this->m_connection);
            }
        }

        auto InputBase::moveToMain() -> void
        {
            Slot::Base::moveToMain();
            Async::MoveToMain(this);
        }
        
        InputBase::~InputBase()
        {
            log_trace(Log::Del, this);
            
            this->disconnect();
        }
    }
}
