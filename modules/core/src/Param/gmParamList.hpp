#pragma once

#include "gmCoreExport.hpp"

#include <QAbstractListModel>

namespace gm
{
    namespace Param
    {
        class Base;
        
        class GM_CORE_EXPORT List : public QAbstractListModel
        {
            Q_OBJECT
        public:
            enum Roles
            {
                Param = Qt::UserRole + 1,
            };
        private:
            QList<Base*> m_params;
        public:
            List();
            auto getParams() -> QList<Base*>;
            auto addParam(Base*) -> void;
            auto removeParam(Base*) -> void;
            auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int;
            auto data(const QModelIndex &index, int role) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            auto moveToMain() -> void;
            ~List();
        };
    }
}
