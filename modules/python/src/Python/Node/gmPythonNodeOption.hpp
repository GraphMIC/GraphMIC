#pragma once

#include "gmPythonNodeParam.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class Option : public Param
            {
                Q_OBJECT
                Q_PROPERTY(int index READ getIndex WRITE setIndex NOTIFY indexChanged);
                Q_PROPERTY(QStringList options READ getOptions NOTIFY optionsChanged);
            private:
                QStringList m_options;
                int m_index;
            public:
                Option(Object*);
                auto setIndex(int) -> void;
                auto getIndex() -> int;
                auto getOptions() -> QStringList;
            public slots:
                void changeOption(const QString&, int);
                void addOption();
                void removeOption();
            signals:
                void optionsChanged();
                void indexChanged();
            };
        }
    }
}