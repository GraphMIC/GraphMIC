#pragma once

#include "gmCoreExport.hpp"

#include <QAbstractListModel>

namespace gm
{
    namespace Slot
    {
        class OutputBase;
        
        class GM_CORE_EXPORT OutputList : public QAbstractListModel
        {
            Q_OBJECT
        public:
            enum Roles
            {
                Slot = Qt::UserRole + 1,
            };
        private:
            QList<OutputBase*> m_slots;
            QHash<QString, OutputBase*> m_slotMap;
        public:
            OutputList();
            auto getSlots() -> QList<OutputBase*>;
            auto addSlot(OutputBase*) -> void;
            auto getSlot(const QString&) -> OutputBase*;
            auto removeSlot(const QString&) -> void;
            auto clear() -> void;
            auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int;
            auto data(const QModelIndex &index, int role) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            auto deleteSlots() -> void;
            auto moveToMain() -> void;
            ~OutputList();
        };
    }
}
