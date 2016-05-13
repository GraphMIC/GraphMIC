#include "gmLog.hpp"
#include "gmPythonScript.hpp"

namespace gm
{
    namespace Python
    {
        Script::Script()
        {
            log_trace(Log::New, this);
        }
        
        auto Script::setSource(const QString& source) -> void
        {
            log_trace(Log::Set);
            
            this->m_source = source;
            emit this->sourceChanged();
        }
        
        auto Script::getSource() -> QString
        {
            log_trace(Log::Get);
            
            return this->m_source;
        }
        
        Script::~Script()
        {
            log_trace(Log::Del);
        }
    }
}