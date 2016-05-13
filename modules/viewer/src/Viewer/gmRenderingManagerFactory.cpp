#include "gmRenderingManagerFactory.hpp"
#include "gmRenderingManager.hpp"

namespace gm
{
    namespace ViewItem
    {
        RenderingManagerFactory::RenderingManagerFactory()
        {
            mitk::RenderingManager::SetFactory( this );
        }

        RenderingManagerFactory::~RenderingManagerFactory()
        {
        }
        
        auto RenderingManagerFactory::CreateRenderingManager() -> mitk::RenderingManager::Pointer const
        {
            RenderingManager::Pointer specificSmartPtr = RenderingManager::New();
            return specificSmartPtr.GetPointer();
        }
    }
}