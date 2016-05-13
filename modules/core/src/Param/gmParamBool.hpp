#pragma once

#include "gmParamBase.hpp"

namespace gm
{
    namespace Param
    {
        class GM_CORE_EXPORT Bool : public Base
        {
            Q_OBJECT
            Q_PROPERTY(bool value READ getValue WRITE setValue NOTIFY valueChanged);
        private:
            bool m_value;
        public:
            static Component::Type ComponentType;
            Bool(const QString&, bool);
            Bool(const QString&);
            auto setValue(bool) -> void;
            auto getValue() -> bool;
            ~Bool();
        signals:
            void valueChanged();
        };
    }
}