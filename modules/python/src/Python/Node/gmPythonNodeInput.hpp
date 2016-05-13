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
            class Input : public Component
            {
                Q_OBJECT
                Q_PROPERTY(int dataTypeID READ getDataTypeID WRITE setDataTypeID NOTIFY dataTypeIDChanged);
                Q_PROPERTY(bool required READ isRequired WRITE setRequired NOTIFY requiredChanged);
                Q_PROPERTY(QString dataTypeString READ getDataTypeString NOTIFY dataTypeStringChanged);
            private:
                Slot::Constraints* m_constraints;
                QString m_dataTypeString;
                bool m_required;
                int m_dataTypeID;
            public:
                Input(Object*);
                auto getConstraints() -> Slot::Constraints*;
                auto setRequired(bool) -> void;
                auto isRequired() -> bool;
                auto setDataTypeID(int) -> void;
                auto getDataTypeID() -> int;
                auto getDataTypeString() -> QString;
            signals:
                void dataTypeStringChanged();
                void dataTypeIDChanged();
                void requiredChanged();
            };
        }
    }
}