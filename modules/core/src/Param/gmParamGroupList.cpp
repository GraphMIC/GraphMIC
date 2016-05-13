#include "gmLogicBase.hpp"
#include "gmParamGroup.hpp"
#include "gmParamGroupList.hpp"

#include "gmLog.hpp"
#include "gmAsync.hpp"

namespace gm
{
    namespace Param
    {
        GroupList::GroupList() : QAbstractListModel(nullptr)
        {
            log_trace(Log::New, this);
        }
        
        auto GroupList::getGroups() -> QList<Group*>
        {
            log_trace(Log::Get);
            
            return this->m_groups;
        }
        
        auto GroupList::addParam(Param::Base* param) -> void
        {
            if (m_groups.count() < 1)
            {
                addGroup("");
            }
            
            auto group = m_groups.first();
                
            group->addParam(param);
        }
        
        auto GroupList::getParam(const QString& paramKey) -> Param::Base*
        {
            for (auto group : this->m_groups)
            {
                auto param = group->getParam(paramKey);
                
                if (param)
                {
                    return param;
                }
            }
            
            throw new std::runtime_error(QString("param [" + paramKey + "] not found").toStdString());
        }
        
        auto GroupList::addGroup(const QString& name) -> void
        {
            log_trace(Log::Func);
            
            int index = this->m_groups.count();
            
            auto group = new Group(name);
            
            beginInsertRows(QModelIndex(), index, index);
            this->m_groups.prepend(group);
            endInsertRows();
            
            this->m_groupMap[name] = group;
        }
        
        auto GroupList::removeGroup(const QString& name) -> void
        {
            log_trace(Log::Func);
            
            auto group  = this->m_groupMap[name];
            int index   = this->m_groups.indexOf(group);
            
            beginRemoveRows(QModelIndex(), index, index);
            this->m_groups.removeOne(group);
            endRemoveRows();
            
            this->m_groupMap.remove(name);
        }
        
        auto GroupList::data(const QModelIndex &index, int role) const -> QVariant
        {
            QVariant v;
            
            if (role == GroupRole && index.isValid())
            {
                v.setValue(this->m_groups.at(index.row()));
            }
            
            return v;
        }
        
        auto GroupList::roleNames() const -> QHash<int, QByteArray>
        {
            QHash<int, QByteArray> roles;
            roles[GroupRole] = "group";
            return roles;
        }
        
        auto GroupList::rowCount(const QModelIndex &parent) const -> int
        {
            return this->m_groups.size();
        }

        auto GroupList::moveToMain() -> void
        {
            for (auto group : this->m_groups)
            {
                group->moveToMain();
            }

            Async::MoveToMain(this);
        }
        
        GroupList::~GroupList()
        {
            log_trace(Log::Del, this);
            
            for (auto group : this->m_groups)
            {
                delete group;
            }
        }
    }
}