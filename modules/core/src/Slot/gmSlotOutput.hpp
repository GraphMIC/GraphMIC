#pragma once

#include "gmSlotOutputBase.hpp"

#include "gmDataImage.hpp"
#include "gmDataVector.hpp"
#include "gmDataNumber.hpp"
#include "gmDataPointset.hpp"

namespace gm
{
    namespace Image
    {
        class Constraints;
    }

    namespace Param
    {
        class Vector;
        class Number;
    }
    
    namespace Connection
    {
        class Object;
    }
    
    namespace Slot
    {
        template <class TData>
        class GM_CORE_EXPORT Output : public OutputBase
        {
        private:
        public:
            static Data::Type DataType;
        public:
            Output(const QString&);
        };

        template <>
        class GM_CORE_EXPORT Output<Data::Image> : public OutputBase
        {
        private:
        public:
            Output(const QString&, Slot::Constraints*);
            auto addImage(Data::Image*) -> void;
            auto getImage(size_t = 0) -> Data::Image*;
        };

        template <>
        class GM_CORE_EXPORT Output<Data::Number> : public OutputBase
        {
        private:
        public:
            Output(const QString&);
            auto addNumber(Data::Number*) -> void;
            auto getNumber(size_t = 0) -> Data::Number*;
        };

        template <>
        class GM_CORE_EXPORT Output<Data::Vector> : public OutputBase
        {
        private:
        public:
            Output(const QString&);
            auto addVector(Data::Vector*) -> void;
            auto getVector(size_t = 0) -> Data::Vector*;
        };

        template <>
        class GM_CORE_EXPORT Output<Data::Pointset> : public OutputBase
        {
        private:
        public:
            Output(const QString&);
            auto addPointset(Data::Pointset*) -> void;
            auto getPointset(size_t = 0) -> Data::Pointset*;
        };
    }
}
