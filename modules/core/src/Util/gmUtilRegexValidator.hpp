#pragma once

#include <QObject>
#include <QRegExp>

#include "gmCoreExport.hpp"

namespace gm
{
    namespace Util
    {
        class GM_CORE_EXPORT RegexValidator : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString regex READ getRegex WRITE setRegex NOTIFY regexChanged);
            Q_PROPERTY(QString input READ getInput WRITE setInput NOTIFY inputChanged);
            Q_PROPERTY(bool match READ getMatch NOTIFY matchChanged);
        private:
            auto checkMatch() -> void;
        private:
            bool m_match;
            QRegExp m_regex;
            QString m_input;
        public:
            RegexValidator();
            auto setRegex(const QString& regex) -> void;
            auto setInput(const QString& input) -> void;
            auto setMatch(bool match) -> void;
            auto getMatch() -> bool;
            auto getRegex() -> QString;
            auto getInput() -> QString;
            ~RegexValidator();
        signals:
            void matchChanged();
            void inputChanged();
            void regexChanged();
        };
    }
}