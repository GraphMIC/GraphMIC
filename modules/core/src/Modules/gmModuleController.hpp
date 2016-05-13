#pragma once

#include "gmCoreExport.hpp"
#include "gmAppController.hpp"

#include <QObject>
#include <QtQml>
#include <QVariantMap>

namespace gm
{
    namespace Module
    {
        class Base;
        
        class GM_CORE_EXPORT Controller : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QVariantMap controllers MEMBER m_controllers NOTIFY controllersChanged);
        private:
            QVariantMap m_controllers;
            Controller();
        public:
            static Controller* instance;
            static auto Create() -> Controller*;
            
            template <class T>
            auto registerController(T* controller, const QString& name) -> void
            {                
                qmlRegisterType<T>();
                
                QVariant variant;
                variant.setValue(controller);
                
                m_controllers[name] = variant;
                
                bla(controller, name);
            }
            
            auto bla(QObject* controller, const QString& name) -> void; //TODO: remove this function
            
            template <class T>
            auto registerType() -> void
            {
                qmlRegisterType<T>();
            }
            
            template <class T>
            auto registerType(const char* ns, const char* name) -> void
            {
                qmlRegisterType<T>(ns, 1, 0, name);
            }
            
            template <class T>
            auto registerInterface(const QString& name) -> void
            {
                qmlRegisterInterface<T>(name.toStdString().c_str());
            }
        signals:
            void controllersChanged();
            void pathsChanged();
        };
    }
}