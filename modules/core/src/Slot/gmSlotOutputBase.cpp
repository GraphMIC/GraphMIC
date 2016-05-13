#include "gmSlotOutputBase.hpp"
#include "gmSlotInputBase.hpp"
#include "gmSlotOutput.hpp"
#include "gmSlotDataList.hpp"

#include "gmConnectionObject.hpp"
#include "gmAsync.hpp"

#include <QJsonObject>

namespace gm
{
    namespace Slot
    {
        Component::Type OutputBase::ComponentType = Component::Type::Output;
        
        OutputBase::OutputBase(const QString& name, Data::Type dataType, Slot::Constraints* imageConstraints) : Base(ComponentType, dataType, name, imageConstraints)
        {
            log_trace(Log::New, this);

            this->m_empty = true;
            this->m_dataCount = 0;
            this->m_dataList = new DataList(this);
        }

        auto OutputBase::setDataCount(int dataCount) -> void
        {
            if (this->m_dataCount != dataCount)
            {
                this->m_dataCount = dataCount;
                emit this->dataCountChanged();

                if (dataCount == 0 && !this->m_empty)
                {
                    this->m_empty = true;
                    emit this->emptyChanged();
                }

                else if (dataCount > 0 && this->m_empty)
                {
                    this->m_empty = false;
                    emit this->emptyChanged();
                }
            }
        }

        auto OutputBase::dataAt(int index) -> QObject*
        {
            return this->getData(index);
        }

        auto OutputBase::clear() -> void
        {
            this->setDataCount(0);
            this->m_dataList->clear();

            emit this->dataChanged();
        }
        
        auto OutputBase::isEmpty() -> bool
        {
            return this->m_empty;
        }

        auto OutputBase::getDataCount() -> int
        {
            return this->m_dataCount;
        }

        auto OutputBase::getDataList() -> DataList*
        {
            return this->m_dataList;
        }
        
        auto OutputBase::onPositionChanged() -> void
        {
            for (auto connection : this->m_connections)
            {
                connection->updateView();
            }
        }
        
        auto OutputBase::addConnection(Connection::Object* connection) -> void
        {
            log_trace(Log::Func);
            
            this->m_inputs.append(connection->getInput());
            this->m_connections.append(connection);
        }
        
        auto OutputBase::removeConnection(Connection::Object* connection) -> void
        {
            log_trace(Log::Func);
            
            this->m_inputs.removeOne(connection->getInput());
            
            if (!this->m_connections.removeOne(connection))
            {
                throw "invalid operation";
            }
        }
        
        auto OutputBase::removeConnections() -> void
        {
            log_trace(Log::Func);
            
            this->m_connections.clear();
            this->m_inputs.clear();
        }
        
        auto OutputBase::connect(InputBase* input) -> void
        {
            log_trace(Log::Func);
            
            if (!input)
            {
                return;
            }
            
            if (this->getNode() == input->getNode())
            {
                return;
            }
            
            if (this->getDataType() != input->getDataType())
            {
                return;
            }
            
            Connection::Create(this, input);
        }

        auto OutputBase::getData(int index) -> Data::Base*
        {
            return this->m_dataList->getData(index);
        }

        auto OutputBase::getInputs() -> QList<InputBase*>
        {
            return this->m_inputs;
        }
        
        auto OutputBase::disconnect() -> void
        {
            log_trace(Log::Func);
            
            for (auto connection : this->m_connections)
            {
                Connection::Delete(connection);
            }
        }

        auto OutputBase::moveToMain() -> void
        {
            Slot::Base::moveToMain();
            Async::MoveToMain(this->m_dataList);
            Async::MoveToMain(this);
        }
        
        OutputBase::~OutputBase()
        {
            log_trace(Log::Del, this);

            this->disconnect();
            this->m_dataList->clear();
        }
    }
}
