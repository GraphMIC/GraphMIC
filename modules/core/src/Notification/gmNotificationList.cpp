#include "gmLog.hpp"

#include "gmNotificationList.hpp"
#include "gmNotificationEntry.hpp"

namespace gm
{
    namespace Notification
    {
        List::List() : QAbstractListModel(nullptr)
        {
            log_trace(Log::New, this);
        }
        
        auto List::getEntries() -> QList<Entry*>
        {
            log_trace(Log::Get);
            
            return this->m_entries;
        }
        
        auto List::clear() -> void
        {
            log_trace(Log::Func);
            
            beginResetModel();
            this->m_entries.clear();
            endResetModel();
        }
        
        auto List::addEntry(Entry* entry) -> void
        {
            log_trace(Log::Func, entry->getInfo().toStdString());
            
            int index = this->m_entries.count();
            
            beginInsertRows(QModelIndex(), index, index);
            this->m_entries.append(entry);
            endInsertRows();
            
            emit this->countChanged();
        }
        
        auto List::removeEntry(Entry* entry) -> void
        {
            log_trace(Log::Func);
            
            int index = this->m_entries.indexOf(entry);
            
            beginRemoveRows(QModelIndex(), index, index);
            this->m_entries.removeOne(entry);
            endRemoveRows();
            
            emit this->countChanged();
        }
        
        auto List::data(const QModelIndex &index, int role) const -> QVariant
        {
            QVariant v;
            
            if (role == EntryRole && index.isValid())
            {
                v.setValue(this->m_entries.at(index.row()));
            }
            
            return v;
        }
        
        auto List::roleNames() const -> QHash<int, QByteArray>
        {
            QHash<int, QByteArray> roles;
            roles[EntryRole] = "entry";
            return roles;
        }
        
        auto List::rowCount(const QModelIndex &parent) const -> int
        {
            return this->m_entries.size();
        }
        
        List::~List()
        {
            log_trace(Log::Del, this);
            
            for (auto entry : this->m_entries)
            {
                delete entry;
            }
        }
    }
}