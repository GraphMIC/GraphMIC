#pragma once

#include <QAbstractListModel>

namespace gm
{
    namespace Data
    {
        class Base;
    }

    namespace Slot
    {
        class OutputBase;

        class GM_CORE_EXPORT DataList : public QAbstractListModel
        {
            Q_OBJECT
        public:
            enum Roles
            {
                DataRole = Qt::UserRole + 1,
            };
        private:
            OutputBase* m_source;
            QList<Data::Base*> m_dataList;
        public:
            DataList() = delete;
            DataList(OutputBase*);
            auto add(Data::Base*) -> void;
            auto getData(int index) -> Data::Base*;
            template <class TData>
            auto get(int index) -> TData*;
            auto clear() -> void;
            auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int;
            auto data(const QModelIndex &index, int role) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            ~DataList();
        };
    }
}
