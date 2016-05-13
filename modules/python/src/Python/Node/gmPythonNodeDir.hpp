#pragma once

#include "gmPythonNodeParam.hpp"

namespace gm
{
    namespace Python
    {
        namespace Node
        {
            class Dir : public Param
            {
                Q_OBJECT
                Q_PROPERTY(QString title READ getTitle WRITE setTitle NOTIFY titleChanged);
            private:
                QString m_title;
            public:
                Dir(Object*);
                auto setTitle(const QString&) -> void;
                auto getTitle() -> QString;
            signals:
                void titleChanged();
            };
        }
    }
}