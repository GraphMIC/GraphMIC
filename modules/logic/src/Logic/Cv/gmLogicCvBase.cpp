#include "gmLogicCvBase.hpp"

namespace gm
{
    namespace Logic
    {
        namespace Cv
        {
            Base::Base(const QString& name) : Logic::Base("cv", name)
            {
                log_trace(Log::New);

                this->setRunnable(true);
                this->setUseTimer(true);
            }
            
            Base::~Base()
            {
                log_trace(Log::Del);
            }
        }
    }
}