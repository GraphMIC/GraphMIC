#include "gmLogicMathBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Math
        {
            Base::Base(const QString& name) : Logic::Base("Math", name)
            {
                log_trace(Log::New);
                
                this->setRunnable(false);
                this->setUseTimer(false);
            }
            
            Base::~Base()
            {
                log_trace(Log::Del);
            }
        }
    }
}