#pragma once

#include "gmSlotInputBase.hpp"
#include "gmDataImage.hpp"
#include "gmDataNumber.hpp"
#include "gmDataVector.hpp"
#include "gmDataPointset.hpp"

namespace gm
{
    namespace Image
    {
        class Constraints;
    }
    
    namespace Slot
    {        
        template <class TData>
        class GM_CORE_EXPORT Input : public InputBase
        {
        public:
            static Data::Type DataType;
        public:
            Input(const QString&, Data::Connection);
        };

        template <>
        class GM_CORE_EXPORT Input<Data::Image> : public InputBase
        {
        private:
        public:
            Input(const QString&, Slot::Constraints*, Data::Connection);
            auto getImage(size_t = 0) -> Data::Image*;
        };

        template <>
        class GM_CORE_EXPORT Input<Data::Number> : public InputBase
        {
        private:
        public:
            Input(const QString&, Data::Connection);
            auto getNumber(size_t = 0) -> Data::Number*;
        };

        template <>
        class GM_CORE_EXPORT Input<Data::Vector> : public InputBase
        {
        private:
        public:
            Input(const QString&, Data::Connection);
            auto getVector(size_t = 0) -> Data::Vector*;
        };

        template <>
        class GM_CORE_EXPORT Input<Data::Pointset> : public InputBase
        {
        private:
        public:
            Input(const QString&, Data::Connection);
            auto getPointset(size_t = 0) -> Data::Pointset*;
        };
    }
}