#include "gmParamList.hpp"
#include "gmParamBase.hpp"
#include "gmLogicBase.hpp"

#include "gmLog.hpp"
#include "gmAsync.hpp"

namespace gm
{
    namespace Param
    {
        List::List() : QAbstractListModel(nullptr)
        {
            log_trace(Log::New, this);
        }
        
        auto List::getParams() -> QList<Base*>
        {
            log_trace(Log::Get);
            
            return this->m_params;
        }
        
        auto List::addParam(Base* param) -> void
        {
            log_trace(Log::Func);
            
            int index = this->m_params.count();
            
            beginInsertRows(QModelIndex(), index, index);
            this->m_params.append(param);
            endInsertRows();
        }
        
        auto List::removeParam(Base* param) -> void
        {
            log_trace(Log::Func);
            
            int index = this->m_params.indexOf(param);
            
            beginRemoveRows(QModelIndex(), index, index);
            this->m_params.removeOne(param);
            endRemoveRows();
        }
        
        auto List::data(const QModelIndex &index, int role) const -> QVariant
        {   
            QVariant v;
            
            if (role == Param && index.isValid())
            {
                v.setValue(this->m_params.at(index.row()));
            }
            
            return v;
        }
            
        auto List::roleNames() const -> QHash<int, QByteArray>
        {
            QHash<int, QByteArray> roles;
            roles[Param] = "param";
            return roles;
        }
            
        auto List::rowCount(const QModelIndex &parent) const -> int
        {
            return this->m_params.size();
        }

        auto List::moveToMain() -> void
        {
            for (auto param : this->m_params)
            {
                param->moveToMain();
            }

            Async::MoveToMain(this);
        }
        
        List::~List()
        {
            log_trace(Log::Del, this);
            
            for (auto param : this->m_params)
            {
                delete param;
            }
        }
    }
}