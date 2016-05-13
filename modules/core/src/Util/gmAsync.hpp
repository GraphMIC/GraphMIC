#pragma once

#include "gmCoreExport.hpp"

#include <functional>
#include <QObject>

namespace gm
{
    namespace Async
    {
        auto GM_CORE_EXPORT Synchronize(std::function<void()>&&) -> void;
        auto GM_CORE_EXPORT Run(std::function<void()>&&) -> void;
        auto GM_CORE_EXPORT MoveToMain(QObject*) -> void;
    }
}