#pragma once

#include <QObject>

namespace gm
{
    namespace App
    {
        class Sidebar : public QObject
        {
            Q_OBJECT
        public:
            Sidebar();
            static Sidebar* instance;
            static auto Create() -> Sidebar*;
            ~Sidebar();
        };
    }
}
