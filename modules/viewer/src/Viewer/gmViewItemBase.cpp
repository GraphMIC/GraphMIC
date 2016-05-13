#include "gmViewItemBase.hpp"

namespace gm
{
    namespace ViewItem
    {
        mitk::DataStorage::Pointer ViewItemBase::storage = nullptr;
        ViewItemBase::ViewItemBase()
        {
            if (storage.IsNotNull())
            {
                storage->AddNodeEvent.AddListener(
                    mitk::MessageDelegate1<ViewItemBase, const mitk::DataNode*>(this, &ViewItemBase::nodeAdded));

                storage->RemoveNodeEvent.AddListener(
                    mitk::MessageDelegate1<ViewItemBase, const mitk::DataNode*>(this, &ViewItemBase::nodeRemoved));

                storage->ChangedNodeEvent.AddListener(
                    mitk::MessageDelegate1<ViewItemBase, const mitk::DataNode*>(this, &ViewItemBase::nodeChanged));
            }
        }

        ViewItemBase::~ViewItemBase()
        {
            if (storage.IsNotNull())
            {
                storage->AddNodeEvent.RemoveListener(
                    mitk::MessageDelegate1<ViewItemBase, const mitk::DataNode*>(this, &ViewItemBase::nodeAdded));

                storage->RemoveNodeEvent.RemoveListener(
                    mitk::MessageDelegate1<ViewItemBase, const mitk::DataNode*>(this, &ViewItemBase::nodeRemoved));

                storage->ChangedNodeEvent.RemoveListener(
                    mitk::MessageDelegate1<ViewItemBase, const mitk::DataNode*>(this, &ViewItemBase::nodeChanged));
            }
        }

        auto ViewItemBase::SetDataStorage(mitk::DataStorage::Pointer dataStorage) -> void
        {
            storage = dataStorage;
        }

        auto ViewItemBase::nodeAdded(const mitk::DataNode* node) -> void
        {
        }

        auto ViewItemBase::nodeChanged(const mitk::DataNode* node) -> void
        {
        }

        auto ViewItemBase::nodeRemoved(const mitk::DataNode* node) -> void
        {
        }
    }
}