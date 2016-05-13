#pragma once

#include "gmIOExceptions.hpp"

#include <QString>
#include <QFileInfo>

namespace gm
{
    namespace IO
    {
        namespace File
        {
            auto GM_CORE_EXPORT Create(const QString& dirPath, const QString& fileName) -> void;
            auto GM_CORE_EXPORT Create(const QString& filePath) -> void;
            
            auto GM_CORE_EXPORT Write(const QString& dirPath, const QString& fileName, const QString& content) -> void;
            auto GM_CORE_EXPORT Write(const QString& filePath, const QString& content) -> void;
            
            auto GM_CORE_EXPORT Read(const QString& dirPath, const QString& fileName) -> QString;
            auto GM_CORE_EXPORT Read(const QString& filePath) -> QString;
            
            auto GM_CORE_EXPORT GetInfo(const QString filePath) -> QFileInfo;
            
            auto GM_CORE_EXPORT SelectExistingFiles(const QString& title, const QString& filter) -> QStringList;
            auto GM_CORE_EXPORT SelectExistingFile(const QString& title, const QString& filter) -> QString;
            auto GM_CORE_EXPORT SelectNewFile(const QString& title, const QString& filter) -> QString;
            
            auto GM_CORE_EXPORT GetFilesFromDirectory(const QString& dirPath, const QString& suffix) -> QStringList;
        }
    }
}