#include "gmParamDir.hpp"
#include "gmIOPath.hpp"

#include <QJsonObject>

namespace gm
{
    namespace Param
    {
        Component::Type Dir::ComponentType = Component::Type::Dir;
        
        Dir::Dir(const QString& name, const QString& title) : Base(ComponentType, name), m_title(title)
        {
            log_trace(Log::New, this);
            
            this->m_dir = IO::Path::ApplicationDir();
        }
        
        auto Dir::setDir(const QString& dir) -> void
        {
            log_trace(Log::Set, dir.toStdString());
            
            if (this->m_dir != dir)
            {
                this->m_dir = dir;
                emit this->dirChanged();
                this->setModified(true);
            }
        }
        
        auto Dir::getDir() -> QString
        {
            log_trace(Log::Get);
            
            return this->m_dir;
        }
        
        auto Dir::setTitle(const QString& title) -> void
        {
            log_trace(Log::Set, title.toStdString());
            
            this->m_title = title;
        }
        
        auto Dir::showDialog() -> void
        {
            log_trace(Log::Func);
         
            this->setDir(IO::Path::SelectExistingDir(this->m_title));
        }
        
        Dir::~Dir()
        {
            log_trace(Log::Del, this);
        }
    }
}