#pragma once

#include <QAbstractListModel>

namespace gm
{
    namespace Notification
    {
        class Entry;
        
        class List : public QAbstractListModel
        {
            Q_OBJECT
            Q_PROPERTY(int count READ rowCount NOTIFY countChanged);
        public:
            enum Roles
            {
                EntryRole = Qt::UserRole + 1,
            };
        private:
            QList<Entry*> m_entries;
        public:
            List();
            auto getEntries() -> QList<Entry*>;
            auto addEntry(Entry*) -> void;
            auto removeEntry(Entry*) -> void;
            auto clear() -> void;
            auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int;
            auto data(const QModelIndex &index, int role) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            ~List();
        signals:
            void countChanged();
        };
    }
}
