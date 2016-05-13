#pragma once

#include "gmLog.hpp"

#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>

namespace gm
{
    namespace Dialog
    {
        class Base : public QObject
        {
            Q_OBJECT
        private:
            QQuickView* m_view;
        private:
            Base() = delete;
        public:
            Base(QString);
            auto show() -> void;
            virtual ~Base() = default;
        public slots:
            void close();
        };
    }
}