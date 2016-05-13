#pragma once

#include "gmParamBase.hpp"

namespace gm
{
    namespace Param
    {
        class GM_CORE_EXPORT Files : public Base
        {
            Q_OBJECT
        private:
            QStringList m_filePaths;
            QString m_filter;
            QString m_title;
        public:
            static Component::Type ComponentType;
            Files(const QString&, const QString&, const QString&);
            auto setTitle(const QString&) -> void;
            auto setFilter(const QString&) -> void;
            auto getFilePaths() -> QStringList;
            ~Files();
        public slots:
            void showDialog();
        };
    }
}