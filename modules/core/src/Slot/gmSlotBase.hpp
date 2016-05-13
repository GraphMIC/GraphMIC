#pragma once

#include "gmComponentBase.hpp"
#include "gmSlotType.hpp"
#include "gmDataType.hpp"

namespace gm
{
    namespace Connection
    {
        class Object;
    }
    
    namespace Slot
    {
        class Constraints;

        class GM_CORE_EXPORT Base : public Component::Base
        {
            Q_OBJECT
            Q_PROPERTY(QString dataTypeString READ getDataTypeString CONSTANT);
            Q_PROPERTY(gm::Slot::Constraints* constraints READ getConstraints NOTIFY constraintsChanged);
            Q_PROPERTY(bool connecting READ getConnecting WRITE setConnecting NOTIFY connectingChanged);
            Q_PROPERTY(int slotTypeID READ getSlotTypeID CONSTANT);
            Q_PROPERTY(int x READ getX WRITE setX NOTIFY xChanged);
            Q_PROPERTY(int y READ getY WRITE setY NOTIFY yChanged);
        private:
            Constraints* m_constraints;
            Data::Type m_dataType;
            Slot::Type m_slotType;
            QString m_dataTypeString;
            bool m_connecting = false;
            int m_x = 0;
            int m_y = 0;
        public:
            Base() = delete;
            Base(Component::Type, Data::Type, const QString&, Constraints*);
            auto setX(int) -> void;
            auto getX() -> int;
            auto setY(int) -> void;
            auto getY() -> int;
            auto setConstraints(Constraints*) -> void;
            auto getConstraints() -> Constraints*;
            auto getDataTypeString() -> QString;
            auto setConnecting(bool) -> void;
            auto getConnecting() -> bool;
            auto getDataType() -> Data::Type;
            auto getSlotType() -> Slot::Type;
            auto getSlotTypeID() -> int;
            virtual auto moveToMain() -> void override;
            virtual auto onPositionChanged() -> void = 0;
            virtual ~Base();
        public slots:
            void connect(Base*);
            void moveConnectX(int);
            void moveConnectY(int);
        signals:
            void constraintsChanged();
            void connectingChanged();
            void xChanged();
            void yChanged();
        };
    }
}