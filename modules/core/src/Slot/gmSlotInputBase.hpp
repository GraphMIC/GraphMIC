#pragma once

#include "gmDataConnection.hpp"
#include "gmCoreExport.hpp"

#include "gmSlotBase.hpp"

namespace gm
{
    namespace Data
    {
        class Base;
    }
    
    namespace Slot
    {
        class OutputBase;
        
        class GM_CORE_EXPORT InputBase : public Base
        {
            Q_OBJECT
            Q_PROPERTY(gm::Slot::OutputBase* output READ getOutput NOTIFY outputChanged);
            Q_PROPERTY(bool required READ isRequired CONSTANT);
        private:
            template <class T> friend class Input;
        private:
            Data::Connection m_dataConnection;
            QList<Data::Base*> m_mockData;
            Connection::Object* m_connection;
        public:
            static Component::Type ComponentType;
            InputBase(const QString&, Data::Type, Data::Connection, Slot::Constraints* = nullptr);
            auto isRequired() -> bool;
            auto getMockData() -> QList<Data::Base*>;
            auto addMockData(Data::Base*) -> void;
            auto clearMockData() -> void;
            auto setConnection(Connection::Object*) -> void;
            auto removeConnection() -> void;
            auto isConnected(OutputBase*) -> bool;
            auto isConnected() -> bool;
            auto onPositionChanged() -> void override;
            auto getOutput() -> OutputBase*;
            auto moveToMain() -> void override;
            ~InputBase();
        public slots:
            void disconnect();
        signals:
            void outputChanged();
        };
    }
}