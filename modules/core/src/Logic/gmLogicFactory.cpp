#include "gmLog.hpp"
#include "gmLogicBase.hpp"
#include "gmLogicFactory.hpp"

namespace gm
{
    namespace Logic
    {
        auto Factory::getMap() -> QHash<QString, std::function<Base*(void)>>&
        {
            static QHash<QString, std::function<Base*(void)>> Map;
            return Map;
        }

        auto Factory::getCustomLogicMap() -> QHash<QString, std::function<Base*(void)>>&
        {
            static QHash<QString, std::function<Base*(void)>> CustomLogicMap;
            return CustomLogicMap;
        }

        auto Factory::Create(const QString& identifier) -> Base*
        {
            log_trace(Log::Func);
            
            auto func = getMap()[identifier];
            
            if (func)
            {
                return func();
            }
            else
            {
                func = getCustomLogicMap()[identifier];

                if (func)
                {
                    return func();
                }
            }
            return nullptr;
        }

        auto Factory::RegisterCustomLogic(const QString& identifier, std::function<Base*(void)> cb) -> void
        {
            getCustomLogicMap()[identifier] = cb;
        }
        
        auto Factory::RegisterLogic(const QString& identifier, std::function<Base*(void)> cb) -> void
        {
            if (getMap().contains(identifier))
            {
                throw new std::runtime_error("logic \"" + identifier.toStdString() + "\" already in factory!");
            }
            else
            {
                getMap()[identifier] = cb;
            }
        }
            
        auto Factory::Count() -> int
        {
            return getMap().size();
        }
    }
}