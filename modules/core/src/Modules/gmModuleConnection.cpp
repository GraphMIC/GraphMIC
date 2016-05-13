#include "gmModuleConnection.hpp"
#include "gmConnectionList.hpp"
#include "gmConnectionView.hpp"
#include "gmConnectionObject.hpp"

namespace gm
{
    namespace Module
    {
        auto Connection::Initialize() -> void
        {
            log_trace(Log::Func);
            
            registerType<gm::Connection::View>("org.graphmic.core.node.connection", "View");
            registerType<gm::Connection::Object>();
            registerType<gm::Connection::List>();
        }
    }
}