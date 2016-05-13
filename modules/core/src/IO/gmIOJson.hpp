#pragma once

#include "gmIOExceptions.hpp"

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace gm
{
    namespace IO
    {
        namespace Json
        {
            auto GM_CORE_EXPORT FromFile(const QString& fullPath) -> QJsonObject;
        }
    }
}