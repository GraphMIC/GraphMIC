#pragma once

#include "gmParamBase.hpp"

namespace gm
{
    namespace Param
    {
        class GM_CORE_EXPORT Dir : public Base
        {
            Q_OBJECT
            Q_PROPERTY(QString dir READ getDir WRITE setDir NOTIFY dirChanged);
        private:
            QString m_dir;
            QString m_title;
        public:
            static Component::Type ComponentType;
            Dir(const QString&, const QString&);
            auto setTitle(const QString&) -> void;
            auto setFilter(const QString&) -> void;
            auto setDir(const QString&) -> void;
            auto getDir() -> QString;
            ~Dir();
        public slots:
            void showDialog();
        signals:
            void dirChanged();
        };
    }
}