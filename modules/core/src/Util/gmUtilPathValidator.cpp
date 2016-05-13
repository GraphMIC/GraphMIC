#include "gmIOPath.hpp"
#include "gmUtilPathValidator.hpp"

namespace gm
{
    namespace Util
    {
        PathValidator::PathValidator()
        {
        }
        
        auto PathValidator::setPath(const QString &path) -> void
        {
            this->m_path = path;
            emit this->pathChanged();
            
            this->setPathExists(IO::Path::Exists(path));
        }
        
        auto PathValidator::setPathExists(bool exists) -> void
        {
            if (this->m_pathExists == exists)
            {
                return;
            }
            
            this->m_pathExists = exists;
            emit this->pathExistsChanged();
        }
        
        auto PathValidator::getPathExists() -> bool
        {
            return this->m_pathExists;
        }
        
        auto PathValidator::getPath() -> QString
        {
            return this->m_path;
        }
        
        PathValidator::~PathValidator()
        {
        }
    }
}