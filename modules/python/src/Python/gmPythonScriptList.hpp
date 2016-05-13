#pragma once

#include <QPoint>
#include <QAbstractListModel>

namespace gm
{
    namespace Python
    {
        class Script;
        
        class ScriptList : public QAbstractListModel
        {
            Q_OBJECT
        public:
            enum Roles
            {
                ScriptRole = Qt::UserRole + 1,
            };
        private:
            QList<Script*> m_scripts;
        public:
            ScriptList();
            auto getScripts() -> QList<Script*>;
            auto addScript(Script*) -> void;
            auto removeScript(Script*) -> void;
            auto clear() -> void;
            auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int;
            auto data(const QModelIndex &index, int role) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            ~ScriptList();
        };
    }
}
