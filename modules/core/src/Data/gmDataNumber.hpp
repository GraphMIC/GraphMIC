#pragma once

#include "gmDataBase.hpp"
#include "gmCoreExport.hpp"

#include <QObject>

namespace gm
{
    namespace Data
    {
        class GM_CORE_EXPORT Number : public Base
        {
            Q_OBJECT
            Q_PROPERTY(bool isNumber READ getIsNumber CONSTANT);
            Q_PROPERTY(double value READ getValue NOTIFY valueChanged);
        private:
            double m_value;
        public:
            static Type DataType;
        private:
            auto getIsNumber() -> bool;
        public:
            Number(double);
            auto setValue(double) -> void;
            auto getValue() -> double;
            ~Number();
        signals:
            void valueChanged();
        };
    }
}
