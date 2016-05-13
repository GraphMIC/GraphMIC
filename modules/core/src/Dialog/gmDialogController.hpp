#pragma once

#include <QObject>

namespace gm
{
    namespace Dialog
    {
        class Controller : public QObject
        {
            Q_OBJECT
        private:
            Controller();
        public:
            static Controller* instance;
            static auto Create() -> Controller*;
            ~Controller();
        public slots:
            void showSettings();
            void showAbout();
        };
    }
}