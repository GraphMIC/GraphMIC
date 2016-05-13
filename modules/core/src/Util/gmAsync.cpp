#include "gmAsync.hpp"
#include "gmApp.hpp"
#include "gmLog.hpp"

#include <QObject>
#include <QThread>
#include <QApplication>
#include <QtConcurrent>

namespace gm
{
    namespace Async
    {
        auto Synchronize(std::function<void()>&& func) -> void
        {
            if (QThread::currentThread() == QApplication::instance()->thread())
            {
                func();
            }
            else
            {
                QObject proxy;
                QObject::connect(&proxy, &QObject::destroyed, Application::instance, std::move(func));
            }
        }

        auto Run(std::function<void(void)>&& func) -> void
        {
            if (QThread::currentThread() == QApplication::instance()->thread())
            {
                QtConcurrent::run(std::move(func));
            }
            else
            {
                func();
            }
        }

        auto MoveToMain(QObject* object) -> void
        {
            auto applicationThread = QApplication::instance()->thread();
            auto currentThread = QThread::currentThread();
            auto objectThread = object->thread();

            if (currentThread != applicationThread && objectThread == currentThread)
            {
                object->moveToThread(applicationThread);
            }
            else
            {
                log_warning("could not move object to main thread!");
            }
        }
    }
}
