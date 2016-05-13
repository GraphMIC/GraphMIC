#include "gmLog.hpp"

#include "gmPythonScriptList.hpp"
#include "gmPythonScript.hpp"

namespace gm
{
    namespace Python
    {
        ScriptList::ScriptList() : QAbstractListModel(nullptr)
        {
            log_trace(Log::New, this);
        }
        
        auto ScriptList::getScripts() -> QList<Script*>
        {
            log_trace(Log::Get);
            
            return this->m_scripts;
        }
        
        auto ScriptList::addScript(Script* script) -> void
        {
            log_trace(Log::Func);
            
            int index = this->m_scripts.count();
            
            beginInsertRows(QModelIndex(), index, index);
            this->m_scripts.append(script);
            endInsertRows();
        }
        
        auto ScriptList::removeScript(Script* script) -> void
        {
            log_trace(Log::Func);
            
            int index = this->m_scripts.indexOf(script);
            
            beginRemoveRows(QModelIndex(), index, index);
            this->m_scripts.removeOne(script);
            endRemoveRows();
        }
        
        auto ScriptList::clear() -> void
        {
            log_trace(Log::Func, this);
            
            auto instances = this->m_scripts;
            
            beginResetModel();
            this->m_scripts.clear();
            endResetModel();
            
            for (auto script : instances)
            {
                delete script;
            }
        }
        
        auto ScriptList::data(const QModelIndex &index, int role) const -> QVariant
        {
            QVariant v;
            
            if (role == ScriptRole && index.isValid())
            {
                v.setValue(this->m_scripts.at(index.row()));
            }
            
            return v;
        }
        
        auto ScriptList::roleNames() const -> QHash<int, QByteArray>
        {
            QHash<int, QByteArray> roles;
            roles[ScriptRole] = "script";
            return roles;
        }
        
        auto ScriptList::rowCount(const QModelIndex &parent) const -> int
        {
            return this->m_scripts.size();
        }
        
        ScriptList::~ScriptList()
        {
            log_trace(Log::Del, this);
            
            this->clear();
        }
    }
}