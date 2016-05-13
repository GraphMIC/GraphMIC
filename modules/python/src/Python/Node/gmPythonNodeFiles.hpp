#pragma once

#include "gmPythonNodeParam.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class Files : public Param
            {
                Q_OBJECT
                Q_PROPERTY(QString title READ getTitle WRITE setTitle NOTIFY titleChanged);
                Q_PROPERTY(QString filter READ getFilter WRITE setFilter NOTIFY filterChanged);
            private:
                QString m_title;
                QString m_filter;
            public:
                Files(Object*);
                auto setTitle(const QString&) -> void;
                auto getTitle() -> QString;
                auto setFilter(const QString&) -> void;
                auto getFilter() -> QString;
            signals:
                void titleChanged();
                void filterChanged();
            };
        }
    }
}