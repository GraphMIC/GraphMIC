#pragma once

#include <QAbstractListModel>

namespace gm
{
    namespace Param
    {
        class Base;
    }
    
    namespace Param
    {
        class Group;
        
        class GM_CORE_EXPORT GroupList : public QAbstractListModel
        {
            Q_OBJECT
        public:
            enum Roles
            {
                GroupRole = Qt::UserRole + 1,
            };
        private:
            QList<Group*> m_groups;
            QHash<QString, Group*> m_groupMap;
        private:
        public:
            GroupList();
            auto getGroups() -> QList<Group*>;
            auto addGroup(const QString&) -> void;
            auto addParam(Param::Base*) -> void;
            auto getParam(const QString&) -> Param::Base*;
            auto removeGroup(const QString&) -> void;
            auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int;
            auto data(const QModelIndex &index, int role) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            auto moveToMain() -> void;
            ~GroupList();
        };
    }
}
