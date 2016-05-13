#pragma once

#include "gmParamBase.hpp"

namespace gm
{
    namespace Param
    {
        class GM_CORE_EXPORT String : public Base
        {
            Q_OBJECT
            Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged);
            Q_PROPERTY(bool valid READ getValid WRITE setValid NOTIFY validChanged);
        private:
            bool m_valid;
            QString m_value;
            QString m_regex;
        public:
            static Component::Type ComponentType;
            String(const QString&, const QString&, const QString&);
            String(const QString&);
            auto setValid(bool) -> void;
            auto getValid() -> bool;
            auto setRegex(const QString&) -> void;
            auto getRegex() -> QString;
            auto setValue(const QString&) -> void;
            auto getValue() -> QString;
            ~String();
        signals:
            void validChanged();
            void valueChanged();
        };
    }
}