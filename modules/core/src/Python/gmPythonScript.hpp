#pragma once

#include <QObject>

namespace gm
{
    namespace Python
    {
        class Script : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged);
        private:
            QString m_source;
        public:
            Script();
            auto setSource(const QString&) -> void;
            auto getSource() -> QString;
            ~Script();
        signals:
            void sourceChanged();
        };
    }
}