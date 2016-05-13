#include "gmLog.hpp"
#include "gmIOJson.hpp"

#include <QFile>

namespace gm
{
    namespace IO
    {
        namespace Json
        {
            auto FromFile(const QString& fullPath) -> QJsonObject
            {
                log_trace(Log::Func, fullPath.toStdString());
                
                QFile file(fullPath);
                
                if (!file.open(QIODevice::ReadOnly))
                {
                    throw new std::runtime_error(Exceptions::FileNotFound);
                }
                
                return QJsonDocument::fromJson(file.readAll()).object();
            }
        }
    }
}
