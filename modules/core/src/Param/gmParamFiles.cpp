#include "gmParamFiles.hpp"
#include "gmIOFile.hpp"
#include "gmIOPath.hpp"
#include "gmNodeObject.hpp"

#include <QJsonObject>

namespace gm
{
    namespace Param
    {
        Component::Type Files::ComponentType = Component::Type::Files;
        
        Files::Files(const QString& name, const QString& title, const QString& filter) : Base(ComponentType, name), m_filter(filter), m_title(title)
        {
            log_trace(Log::New, this);
        }
        
        auto Files::getFilePaths() -> QStringList
        {
            log_trace(Log::Get);
            
            return this->m_filePaths;
        }
        
        auto Files::setTitle(const QString& title) -> void
        {
            log_trace(Log::Set, title.toStdString());
            
            this->m_title = title;
        }
        
        auto Files::setFilter(const QString& filter) -> void
        {
            log_trace(Log::Set, filter.toStdString());
            
            this->m_filter = filter;
        }
        
        auto Files::showDialog() -> void
        {
            log_trace(Log::Func);
            
            this->m_filePaths = IO::File::SelectExistingFiles(this->m_title, this->m_filter);
            
            if (m_filePaths.length() > 0)
            {
                if (this->m_filePaths.length() > 0)
                {
                    ///todo
                    this->getNode()->execute();
                }
            }
        }
        
        Files::~Files()
        {
            log_trace(Log::Del, this);
        }
    }
}