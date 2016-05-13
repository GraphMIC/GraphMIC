#pragma once

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
        class InputBase;
        class DataList;
        
        class GM_CORE_EXPORT OutputBase : public Base
        {
            Q_OBJECT
            Q_PROPERTY(gm::Slot::DataList* dataList READ getDataList CONSTANT);
            Q_PROPERTY(int dataCount READ getDataCount NOTIFY dataCountChanged);
            Q_PROPERTY(bool empty READ isEmpty NOTIFY emptyChanged);
        private:
            template <class T> friend class Output;
        private:
            QList<Connection::Object*> m_connections;
            QList<InputBase*> m_inputs;
            DataList* m_dataList;
            int m_dataCount;
            bool m_empty;
        private:
            auto getDataList() -> DataList*;
        public:
            static Component::Type ComponentType;
            OutputBase(const QString&, Data::Type, Slot::Constraints* = nullptr);
            auto addConnection(Connection::Object*) -> void;
            auto removeConnection(Connection::Object*) -> void;
            auto isEmpty() -> bool;
            auto removeConnections() -> void;
            auto onPositionChanged() -> void override;
            auto getInputs() -> QList<InputBase*>;
            auto connect(InputBase*) -> void;
            auto setDataCount(int) -> void;
            auto getDataCount() -> int;
            auto getData(int) -> Data::Base*;
            auto clear() -> void;
            auto moveToMain() -> void override;
            ~OutputBase();
        public slots:
            void disconnect();
            QObject* dataAt(int);
        signals:
            void dataCountChanged();
            void emptyChanged();
            void dataChanged();
        };
    }
}
