#pragma once

#include <QObject>

namespace gm
{
    namespace Util
    {
        class GM_CORE_EXPORT PathValidator : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(bool pathExists READ getPathExists NOTIFY pathExistsChanged);
            Q_PROPERTY(QString path READ getPath WRITE setPath NOTIFY pathChanged);
        private:
            bool m_pathExists;
            QString m_path;
        public:
            PathValidator();
            auto setPathExists(bool exists) -> void;
            auto setPath(const QString& path) -> void;
            auto getPathExists() -> bool;
            auto getPath() -> QString;
            ~PathValidator();
        signals:
            void pathChanged();
            void pathExistsChanged();
        };
    }
}