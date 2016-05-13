#include "gmLog.hpp"
#include "gmIOFile.hpp"
#include "gmIOPath.hpp"

#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>
#include <QFileDialog>

#include <exception>

namespace gm
{
    namespace IO
    {
        auto File::Create(const QString& filePath) -> void
        {
            log_trace(Log::Func);
            
            Write(filePath, "");
        }
        
        auto File::Create(const QString& dirPath, const QString& fileName) -> void
        {
            log_trace(Log::Func);
            
            Create(dirPath + "/" + fileName);
        }
        
        auto File::Write(const QString& filePath, const QString& content) -> void
        {
            log_trace(Log::Func);
            
            auto path = Path::ExtractFilePath(filePath);
            QDir dir(path);

            if (!dir.exists())
            {
                dir.mkpath(".");
            }
            
            QFile file(filePath);
                
            if (file.open(QIODevice::WriteOnly))
            {
                if (!content.isEmpty())
                {
                    QTextStream stream(&file);
                    stream << content << endl;
                }
                    
                file.close();
            }
            
            else throw new std::runtime_error(Exceptions::FileNotFound);
        }
                
        auto File::Write(const QString& dirPath, const QString& fileName, const QString& content) -> void
        {
            log_trace(Log::Func);
            
            Write(dirPath + "/" + fileName, content);
        }
                
        auto File::Read(const QString& filePath) -> QString
        {
            log_trace(Log::Func);
            
            QString content;
            
            QFile file(filePath);
            
            if (file.open(QIODevice::ReadOnly))
            {
                QTextStream stream(&file);
                content = file.readAll();
                file.close();
            }
            
            return content;
        }
                
        auto File::Read(const QString& dirPath, const QString& fileName) -> QString
        {
            log_trace(Log::Func);
            
            return Read(dirPath + "/" + fileName);
        }
                    
        auto File::GetInfo(const QString filePath) -> QFileInfo
        {
            log_trace(Log::Func);
            
            QFileInfo info(filePath);
            return info;
        }
        
        auto File::SelectExistingFiles(const QString& title, const QString& filter) -> QStringList
        {
            log_trace(Log::Func);
            
            return QFileDialog::getOpenFileNames(0, title, 0, filter);
        }
         
        auto File::SelectExistingFile(const QString &title, const QString &filter) -> QString
        {
            log_trace(Log::Func);
            
            return QFileDialog::getOpenFileName(0, title, 0, filter);
        }
                    
        auto File::SelectNewFile(const QString& title, const QString& filter) -> QString
        {
            log_trace(Log::Func);
            
            return QFileDialog::getSaveFileName(0, title, 0, filter);
        }
                    
        auto File::GetFilesFromDirectory(const QString& dirPath, const QString& suffix) -> QStringList
        {
            log_trace(Log::Func);
            
            QDirIterator it(dirPath);
            QStringList filePaths;
            QRegExp regex(suffix);
            
            while (it.hasNext())
            {
                auto path = it.next();
                auto file = it.fileName();
                
                if (!file.compare(".") || !file.compare(".."))
                {
                    continue;
                }
                
                if (suffix.length() > 0) // blorz
                {
                    if (regex.indexIn(it.fileInfo().suffix()))
                    {
                        filePaths.append(path);
                    }
                }
                else
                {
                    filePaths.append(path);
                }
            }
            
            return filePaths;
        }
    }
}