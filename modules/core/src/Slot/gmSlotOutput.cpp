#include "gmSlotOutput.hpp"

#include "gmNotificationController.hpp"
#include "gmConnectionObject.hpp"
#include "gmNodeEditor.hpp"
#include "gmSlotDataList.hpp"
#include "gmSlotConstraints.hpp"
#include "gmParamVector.hpp"
#include "gmAsync.hpp"

namespace gm
{
    namespace Slot
    {
        template <class TData> Data::Type Output<TData>::DataType = TData::DataType;
        
        template <class TData>
        Output<TData>::Output(const QString& name) : OutputBase(name, TData::DataType)
        {
            log_trace(Log::New, this);
        }

        Output<Data::Image>::Output(const QString& name, Slot::Constraints* imageConstraints) : OutputBase(name, Data::Type::Image, imageConstraints)
        {
            log_trace(Log::New, this);
        }

        Output<Data::Number>::Output(const QString& name) : OutputBase(name, Data::Type::Number)
        {

        }

        Output<Data::Vector>::Output(const QString& name) : OutputBase(name, Data::Type::Vector)
        {
        }

        Output<Data::Pointset>::Output(const QString& name) : OutputBase(name, Data::Type::Pointset)
        {

        }

        auto Output<Data::Image>::getImage(size_t index) -> Data::Image*
        {
            return this->m_dataList->get<Data::Image>(index);
        }

        auto Output<Data::Image>::addImage(Data::Image* image) -> void
        {
            log_trace(Log::Func);

            if (!image)
            {
                log_error("empty image will be skipped!");
                return;
            }

            this->m_dataList->add(image);
        }

        auto Output<Data::Number>::addNumber(Data::Number* number) -> void
        {
            Async::MoveToMain(number);
            this->m_dataList->add(number);
        }

        auto Output<Data::Number>::getNumber(size_t index) -> Data::Number*
        {
            return this->m_dataList->get<Data::Number>(index);
        }

        auto Output<Data::Vector>::addVector(Data::Vector* vector) -> void
        {
            Async::MoveToMain(vector);
            this->m_dataList->add(vector);
        }

        auto Output<Data::Vector>::getVector(size_t index) -> Data::Vector*
        {
            return this->m_dataList->get<Data::Vector>(index);
        }

        auto Output<Data::Pointset>::addPointset(Data::Pointset* pointset) -> void
        {
            Async::MoveToMain(pointset);
            this->m_dataList->add(pointset);
        }

        auto Output<Data::Pointset>::getPointset(size_t index) -> Data::Pointset*
        {
            return this->m_dataList->get<Data::Pointset>(index);
        }

        template class Output<Data::Image>;
        template class Output<Data::Vector>;
        template class Output<Data::Number>;
        template class Output<Data::Pointset>;
    }
}