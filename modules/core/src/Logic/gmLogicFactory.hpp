#pragma once

#include "gmCoreExport.hpp"

#include <functional>
#include <QString>
#include <QHash>

namespace gm
{
    namespace Logic
    {
        class Base;
        
        class GM_CORE_EXPORT Factory
        {
        private:
            static QHash<QString, std::function<Base*(void)>> Map;
            static QHash<QString, std::function<Base*(void)>> CustomLogicMap;
            static auto getMap() -> QHash<QString, std::function<Base*(void)>>&;
            static auto getCustomLogicMap() -> QHash<QString, std::function<Base*(void)>>&;
        public:
            static auto RegisterLogic(const QString&, std::function<Base*(void)>) -> void;
            static auto RegisterCustomLogic(const QString&, std::function<Base*(void)>) -> void;
            static auto Create(const QString&) -> Base*;
            static auto Count() -> int;
        };
    }
}