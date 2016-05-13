#pragma once

#include "gmDialogBase.hpp"

namespace gm
{
    namespace Dialog
    {
        class DeleteFile : public Base
        {
            Q_OBJECT
        public:
            DeleteFile();
            static DeleteFile* instance;
            static auto Show() -> void;
        public slots:
            void ok();
            void cancel();
        };
    }
}