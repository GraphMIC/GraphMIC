#include "gmLog.hpp"

#include "gmNodeFactory.hpp"
#include "gmNodeObject.hpp"

#include "gmLogicFactory.hpp"
#include "gmLogicBase.hpp"

namespace gm
{
    namespace Node
    {
        auto Factory::Create(const QString& identifier) -> Object*
        {
            log_trace(Log::Func, identifier.toStdString());
            
            auto logic = Logic::Factory::Create(identifier);
            
            if (logic)
            {
                return logic->getNode();
            }
 
            return nullptr;
        }
    }
}