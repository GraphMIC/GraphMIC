#pragma once

#include "gmAppMenu.hpp"

#include <QObject>
#include <QVariantMap>

class QQmlEngine;
class QJSEngine;

namespace gm
{
    namespace App
    {
        class Config;
        
        class Controller : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(bool debugBuild READ isDebugBuild CONSTANT);
            Q_PROPERTY(QString version READ getVersion CONSTANT);
            Q_PROPERTY(QVariantMap controllers READ getControllers CONSTANT);
        private:
            static QVariantMap m_controllers;
            QString m_version;
            Controller();
        public:
            auto init() -> void;
            auto getControllers() -> QVariantMap;
            auto setVersion(QString) -> void;
            auto getVersion() -> QString;
            auto isDebugBuild() -> bool;
            static auto registerController(QObject*, const QString&) -> void;
            static QObject* InstanceProvider(QQmlEngine*, QJSEngine*);
            static Controller* instance;
            static auto Create() -> Controller*;
            ~Controller();
        signals:
            void viewControllerChanged();
        };
    }
}