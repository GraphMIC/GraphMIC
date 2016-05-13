#pragma once

#include "gmCoreExport.hpp"

#include <QObject>
#include <QHash>

namespace gm
{
    namespace Param
    {
        class List;
        class Base;

        class GM_CORE_EXPORT Group : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(int size READ getSize NOTIFY sizeChanged);
            Q_PROPERTY(bool expanded READ getExpanded NOTIFY expandedChanged);
            Q_PROPERTY(gm::Param::List* paramList READ getParamList CONSTANT);
            Q_PROPERTY(QString name READ getName CONSTANT);
        private:
            QHash<QString, Base*> m_paramMap;
            List* m_paramList;
            QString m_name;
            bool m_expanded;
            int m_size;
        public:
            Group() = delete;
            Group(const QString&);
            auto setExpanded(bool) -> void;
            auto getExpanded() -> bool;
            auto getParamList() -> List*;
            auto addParam(Base*) -> void;
            auto getParam(const QString&) -> Base*;
            auto removeParam(const QString&) -> void;
            auto getName() -> QString;
            auto getSize() -> int;
            auto moveToMain() -> void;
            ~Group();
        public slots:
            void toggleExpansion();
        signals:
            void sizeChanged();
            void expandedChanged();
        };
    }
}