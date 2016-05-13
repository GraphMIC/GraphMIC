#pragma once

#include "gmCoreExport.hpp"

#include <QObject>

namespace gm
{
    namespace Node
    {
        class GM_CORE_EXPORT Search : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(bool visible READ getVisible WRITE setVisible NOTIFY visibleChanged);
            Q_PROPERTY(QString query READ getQuery WRITE setQuery NOTIFY queryChanged);
            Q_PROPERTY(QList<QObject*> matches READ getMatches NOTIFY matchesChanged);
        private:
            static auto GetEntries() -> QList<QObject*>&;
            QList<QObject*> m_matches;
            bool m_visible;
            QString m_query;
            Search();
        public:
            static Search* instance;
            auto setQuery(const QString&) -> void;
            auto getQuery() -> QString;
            auto setVisible(bool) -> void;
            auto getVisible() -> bool;
            auto getMatches() -> QList<QObject*>;
            auto updateMatches() -> void;
            auto contains(const QString& identifier) -> bool;
            static auto Create() -> Search*;
            static auto AddEntry(const QString& identifier) -> void;
            ~Search();
        public slots:
            void processQuery();
        signals:
            void matchesChanged();
            void visibleChanged();
            void queryChanged();
        };
    }
}
