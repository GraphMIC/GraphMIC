#include "gmLogicGenericBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Generic
        {
            Base::Base(const QString& name) : Logic::Base("Generic", name)
            {
                log_trace(Log::New, this);
            }
            
            Base::~Base()
            {
                log_trace(Log::Del, this);
            }
        }
    }
}