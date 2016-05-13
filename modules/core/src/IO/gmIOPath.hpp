#pragma once

#include "gmIOExceptions.hpp"

#include <QString>
#include <QList>
#include <QFileInfo>

namespace gm
{
    namespace IO
    {
        namespace Path
        {
            auto GM_CORE_EXPORT GetFileInfos(const QString& dirPath) -> QList<QFileInfo>;
            auto GM_CORE_EXPORT SelectExistingDir(const QString& title) -> QString;
            auto GM_CORE_EXPORT ExtractFileName(const QString& fullPath) -> QString;
            auto GM_CORE_EXPORT ExtractFilePath(const QString& fullPath) -> QString;
            auto GM_CORE_EXPORT ApplicationDir() -> QString;
            auto GM_CORE_EXPORT MakeDir(const QString& path, const QString& name) -> void;
            auto GM_CORE_EXPORT Exists(const QString& path) -> bool;
            auto GM_CORE_EXPORT IsDir(const QString& filePath) -> bool;
        }
    }
}