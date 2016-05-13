#include "gmSlotInputBase.hpp"
#include "gmSlotInputList.hpp"

#include "gmAsync.hpp"
#include "gmLog.hpp"

namespace gm
{
    namespace Slot
    {
        InputList::InputList() : QAbstractListModel(nullptr)
        {
            log_trace(Log::New, this);
        }
        
        auto InputList::getSlots() -> QList<InputBase*>
        {
            log_trace(Log::Get);
            
            return this->m_slots;
        }
        
        auto InputList::addSlot(InputBase* slot) -> void
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

        auto InputList::getSlot(const QString& key) -> InputBase*
        {
            auto slot = this->m_slotMap[key];
            
            if (!slot)
            {
                throw new std::runtime_error("Could not get Slot \'" + key.toStdString() + "\'");
            }
            
            return slot;
        }
        
        void InputList::removeSlot(const QString& key)
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
        
        auto InputList::data(const QModelIndex &index, int role) const -> QVariant
        {
            QVariant v;
            
            if (role == Slot && index.isValid())
            {
                v.setValue(this->m_slots.at(index.row()));
            }
            
            return v;
        }
            
        auto InputList::roleNames() const -> QHash<int, QByteArray>
        {
            QHash<int, QByteArray> roles;
            roles[Slot] = "slot";
            return roles;
        }
            
        auto InputList::rowCount(const QModelIndex &parent) const -> int
        {
            return this->m_slots.size();
        }

        auto InputList::moveToMain() -> void
        {
            for (auto input : this->m_slots)
            {
                input->moveToMain();
            }

            Async::MoveToMain(this);
        }
        
        InputList::~InputList()
        {
            log_trace(Log::Del, this);
            
            for (auto slot : this->m_slots)
            {
                delete slot;
            }
        }
    }
}