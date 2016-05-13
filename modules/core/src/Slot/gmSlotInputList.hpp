#pragma once

#include <QAbstractListModel>

namespace gm
{
    namespace Slot
    {
        class InputBase;
        
        class GM_CORE_EXPORT InputList : public QAbstractListModel
        {
            Q_OBJECT
        public:
            enum Roles
            {
                Slot = Qt::UserRole + 1,
            };
        private:
            QList<InputBase*> m_slots;
            QHash<QString, InputBase*> m_slotMap;
        public:
            InputList();
            auto getSlots() -> QList<InputBase*>;
            auto addSlot(InputBase*) -> void;
            auto getSlot(const QString&) -> InputBase*;
            auto removeSlot(const QString&) -> void;
            auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int;
            auto data(const QModelIndex &index, int role) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            auto moveToMain() -> void;
            ~InputList();
        };
    }
}
