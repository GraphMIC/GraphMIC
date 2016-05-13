#pragma once

#include "gmViewerExport.hpp"

#include <mitkDataStorage.h>

#include <QQuickItem>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT ViewItemBase : public QQuickItem
        {
        protected:
            static mitk::DataStorage::Pointer storage;
        public:
            ViewItemBase();
            ~ViewItemBase();
            static auto SetDataStorage(mitk::DataStorage::Pointer dataStorage) -> void;
            virtual auto nodeAdded(const mitk::DataNode* node) -> void;
            virtual auto nodeChanged(const mitk::DataNode* node) -> void;
            virtual auto nodeRemoved(const mitk::DataNode* node) -> void;
        };
    }
}


