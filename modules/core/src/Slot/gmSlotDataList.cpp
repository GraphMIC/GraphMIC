#include "gmLog.hpp"
#include "gmAsync.hpp"

#include "gmSlotOutputBase.hpp"
#include "gmSlotDataList.hpp"
#include "gmDataBase.hpp"

namespace gm
{
    namespace Slot
    {
        DataList::DataList(OutputBase* source) : QAbstractListModel(nullptr), m_source(source)
        {
            log_trace(Log::New, this);
        }

        auto DataList::add(Data::Base* data) -> void
        {
            log_trace(Log::Func, data);

            Async::MoveToMain(data);
            Async::Synchronize([this, data](){
                int index = this->m_dataList.count();

                beginInsertRows(QModelIndex(), index, index);
                this->m_dataList.append(data);
                endInsertRows();

                this->m_source->setDataCount(this->m_dataList.count());
            });
        }

        auto DataList::getData(int index) -> Data::Base*
        {
            if (index >= this->m_dataList.count())
            {
                return nullptr;
            }

            return this->m_dataList.at(index);
        }

        template <class TData> auto DataList::get(int index) -> TData*
        {
            if (index >= this->m_dataList.count())
            {
                return nullptr;
            }

            return this->m_dataList.at(index)->as<TData>();
        }

        auto DataList::clear() -> void
        {
            log_trace(Log::Func);

            for (auto data : this->m_dataList)
            {
                delete data;
            }

            this->m_dataList.clear();
            this->m_source->setDataCount(0);
        }

        auto DataList::data(const QModelIndex &index, int role) const -> QVariant
        {
            QVariant v;

            if (role == DataRole && index.isValid())
            {
                v.setValue(this->m_dataList.at(index.row()));
            }

            return v;
        }

        auto DataList::roleNames() const -> QHash<int, QByteArray>
        {
            QHash<int, QByteArray> roles;
            roles[DataRole] = "data";
            return roles;
        }

        auto DataList::rowCount(const QModelIndex &parent) const -> int
        {
            return this->m_dataList.size();
        }

        DataList::~DataList()
        {
            log_trace(Log::Del, this);

            clear();
        }

        template auto DataList::get<Data::Image>(int index) -> Data::Image*;
        template auto DataList::get<Data::Number>(int index) -> Data::Number*;
        template auto DataList::get<Data::Vector>(int index) -> Data::Vector*;
        template auto DataList::get<Data::Pointset>(int index) -> Data::Pointset*;
    }
}