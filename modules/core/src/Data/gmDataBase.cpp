#include "gmDataBase.hpp"

#include "gmDataImage.hpp"
#include "gmDataNumber.hpp"
#include "gmDataVector.hpp"
#include "gmDataPointset.hpp"

#include "gmDebugController.hpp"

namespace gm
{
    namespace Data
    {
        Base::Base(Data::Type dataType) : m_dataType(dataType)
        {
            Debug::Controller::instance->incDataCount();
        }

        template <class TData>
        auto Base::as() -> TData*
        {
            if (this->m_dataType == TData::DataType)
            {
                return reinterpret_cast<TData*>(this);
            }

            return nullptr;
        }

        auto Base::getDataType() -> Type
        {
            return this->m_dataType;
        }

        Base::~Base()
        {
            Debug::Controller::instance->decDataCount();
        }

        template auto Base::as<Data::Image>() -> Data::Image*;
        template auto Base::as<Data::Number>() -> Data::Number*;
        template auto Base::as<Data::Vector>() -> Data::Vector*;
        template auto Base::as<Data::Pointset>() -> Data::Pointset*;
    }
}
