#pragma once

#include "gmPythonNodeComponent.hpp"

#include <QObject>

namespace gm
{
    namespace Slot
    {
        class Constraints;
    }

    namespace Python
    {
        namespace Node
        {
            class Output : public Component
            {
                Q_OBJECT
                Q_PROPERTY(int dataTypeID READ getDataTypeID WRITE setDataTypeID NOTIFY dataTypeIDChanged);
                Q_PROPERTY(QString dataTypeString READ getDataTypeString NOTIFY dataTypeStringChanged);
            private:
                Slot::Constraints* m_constraints;
                QString m_dataTypeString;
                int m_dataTypeID;
            public:
                Output(Object*);
                auto getConstraints() -> Slot::Constraints*;
                auto setDataTypeID(int) -> void;
                auto getDataTypeID() -> int;
                auto getDataTypeString() -> QString;
            signals:
                void dataTypeStringChanged();
                void dataTypeIDChanged();
            };
        }
    }
}