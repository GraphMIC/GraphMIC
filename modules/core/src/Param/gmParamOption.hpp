#pragma once

#include "gmParamBase.hpp"

namespace gm
{
    namespace Param
    {
        class GM_CORE_EXPORT Option : public Base
        {
            Q_OBJECT
            Q_PROPERTY(int index READ getIndex WRITE setIndex NOTIFY indexChanged);
            Q_PROPERTY(QStringList options READ getOptions WRITE setOptions NOTIFY optionsChanged);
        private:
            int m_index;
            QStringList m_options;
        public:
            static Component::Type ComponentType;
            Option(const QString&, QStringList, int);
            Option(const QString&, QStringList);
            auto setOptions(QStringList) -> void;
            auto getOptions() -> QStringList;
            auto setIndex(int) -> void;
            auto getIndex() -> int;
            ~Option();
        signals:
            void optionsChanged();
            void indexChanged();
        };
    }
}