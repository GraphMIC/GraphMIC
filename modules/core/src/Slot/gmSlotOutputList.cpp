#include "gmSlotOutputBase.hpp"
#include "gmSlotOutputList.hpp"

#include "gmAsync.hpp"
#include "gmLog.hpp"

namespace gm
{
    namespace Slot
    {
        OutputList::OutputList() : QAbstractListModel(nullptr)
        {
            log_trace(Log::New, this);
        }
        
        auto OutputList::getSlots() -> QList<OutputBase*>
        {
            log_trace(Log::Get);
            
            return this->m_slots;
        }
        
        auto OutputList::addSlot(OutputBase* slot) -> void
        {
            log_trace(Log::Func);
            
            auto key = slot->getName();
            
            if (this->m_slotMap[key])
            {
                throw new std::runtime_error("Could not get Slot \'" + key.toStdString() + "\'");
            }
            
            this->m_slotMap[key] = slot;
            int index = this->m_slots.count();
            
            beginInsertRows(QModelIndex(), index, index);
            this->m_slots.append(slot);
            endInsertRows();
        }
        
        auto OutputList::getSlot(const QString& key) -> OutputBase*
        {
            auto slot = this->m_slotMap[key];
            
            if (!slot)
            {
                throw new std::runtime_error("Could not get Slot \'" + key.toStdString() + "\'");
            }
            
            return slot;
        }
        
        void OutputList::removeSlot(const QString& key)
        {
            log_trace(Log::Func);
            
            auto slot = this->m_slotMap[key];
            
            if (!slot)
            {
                throw new std::runtime_error("Could not remove Slot \'" + key.toStdString() + "\'");
            }
            
            int index = this->m_slots.indexOf(slot);
            
            beginRemoveRows(QModelIndex(), index, index);
            auto error = !this->m_slots.removeOne(slot);
            endRemoveRows();
            
            if (error)
            {
                throw new std::runtime_error("Could not remove Slot \'" + key.toStdString() + "\'");
            }
            
            if (!this->m_slotMap.remove(key))
            {
                throw new std::runtime_error("Could not remove Slot \'" + key.toStdString() + "\'");
            }
        }
        
        auto OutputList::data(const QModelIndex &index, int role) const -> QVariant
        {
            QVariant v;
            
            if (role == Slot && index.isValid())
            {
                v.setValue(this->m_slots.at(index.row()));
            }
            
            return v;
        }
        
        auto OutputList::roleNames() const -> QHash<int, QByteArray>
        {
            QHash<int, QByteArray> roles;
            roles[Slot] = "slot";
            return roles;
        }
        
        auto OutputList::rowCount(const QModelIndex &parent) const -> int
        {
            return this->m_slots.size();
        }

        auto OutputList::clear() -> void
        {
            beginResetModel();
            this->m_slots.clear();
            this->m_slotMap.clear();
            endResetModel();
        }

        auto OutputList::deleteSlots() -> void
        {
            for (auto slot : this->m_slots)
            {
                delete slot;
            }
        }

        auto OutputList::moveToMain() -> void
        {
            for (auto output : this->m_slots)
            {
                output->moveToMain();
            }

            Async::MoveToMain(this);
        }
        
        OutputList::~OutputList()
        {
            log_trace(Log::Del, this);
        }
    }
}