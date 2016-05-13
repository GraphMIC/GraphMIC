#include "gmLog.hpp"
#include "gmIOPath.hpp"
#include "gmIOFile.hpp"

#include <QFileDialog>
#include <QDirIterator>

namespace gm
{
    namespace IO
    {
        auto Path::ApplicationDir() -> QString
        {
            return QDir::currentPath();
        }
        
        auto Path::GetFileInfos(const QString& dirPath) -> QList<QFileInfo>
        {
            log_trace(Log::Func);
            
            QDirIterator it(dirPath, QDir::AllEntries | QDir::Hidden | QDir::System);
            QList<QFileInfo> infoList;
            
            while (it.hasNext())
            {
                auto absName = it.next();
                auto relName = it.fileName();
                
                if (relName == "." || relName == "..")
                    continue;
                
                infoList.append(it.fileInfo());
            }
            
            return infoList;
        }
        
        auto Path::ExtractFilePath(const QString& fullPath) -> QString
        {
            log_trace(Log::Func);
            
            return fullPath.left(fullPath.lastIndexOf('/'));
        }
        
        auto Path::ExtractFileName(const QString& fullPath) -> QString
        {
            log_trace(Log::Func);
            
             return fullPath.mid(fullPath.lastIndexOf('/') + 1, fullPath.length() - 1);
        }
        
        auto Path::Exists(const QString &path) -> bool
        {
            log_trace(Log::Func);
            
            return QFile(path).exists();
        }
        
        auto Path::IsDir(const QString& filePath) -> bool
        {
            log_trace(Log::Func);
            
            return File::GetInfo(filePath).isDir();
        }
        
        auto Path::SelectExistingDir(const QString& title) -> QString
        {
            return QFileDialog::getExistingDirectory(0, title, 0);
        }
        
        auto Path::MakeDir(const QString& path, const QString& name) -> void
        {
            log_trace(Log::Func);
            
            QString fullPath = path + "/" + name;
            QDir dir(fullPath);
            
            if (!dir.exists())
            {
                dir.mkpath(".");
            }
        }
    }
}