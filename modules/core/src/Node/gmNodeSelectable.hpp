#pragma once

#include "gmCoreExport.hpp"

#include <QObject>
#include <functional>

namespace gm
{
    namespace Node
    {
        class GM_CORE_EXPORT Selectable : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(bool selected READ getSelected WRITE setSelected NOTIFY selectedChanged);
        private:
            bool m_selected;
        public:
            std::function<void(void)> onSelected;
        public:
            Selectable();
            auto setSelected(bool) -> void;
            auto getSelected() -> bool;
            virtual auto deleteObject() -> void = 0;
            virtual ~Selectable();
        public slots:
            void select();
        signals:
            void selectedChanged();
        };
    }
}