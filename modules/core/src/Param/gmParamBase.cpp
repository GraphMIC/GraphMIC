#include "gmParamBase.hpp"
#include "gmLogicBase.hpp"
#include "gmParamList.hpp"

namespace gm
{
    namespace Param
    {
        Base::Base(Component::Type componentType, const QString& name) : Component::Base(componentType, name)
        {
        }
        
        Base::~Base()
        {
        }
    }
}

