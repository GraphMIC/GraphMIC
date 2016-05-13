#include "gmDialogDeleteFile.hpp"

namespace gm
{
    namespace Dialog
    {
        DeleteFile* DeleteFile::instance = nullptr;
        
        DeleteFile::DeleteFile() : Base("DeleteFile")
        {
            log_trace(Log::New, this);
        }
        
        auto DeleteFile::cancel() -> void
        {
            log_trace(Log::Func);
            
            this->close();
        }
        
        auto DeleteFile::ok() -> void
        {
            log_trace(Log::Func);
            
            this->close();
        }
        
        auto DeleteFile::Show() -> void
        {
            log_trace(Log::Func);
            
            if (!instance)
            {
                instance = new DeleteFile();
            }
            
            instance->show();
        }
    }
}
