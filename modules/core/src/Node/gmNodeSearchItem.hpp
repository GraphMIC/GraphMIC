#pragma once

#include <QObject>

namespace gm
{
    namespace Node
    {
        class Search;
        
        class SearchItem : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString name READ getName CONSTANT);
            Q_PROPERTY(QString prefix READ getPrefix CONSTANT);
        private:
            friend class Search;
            QString m_name;
            QString m_prefix;
        public:
            SearchItem() = delete;
            SearchItem(const QString&, const QString&);
            auto contains(const QString&) -> bool;
            auto matches(const QString&) -> bool;
            auto getName() -> QString;
            auto getPrefix() -> QString;
        };
    }
}