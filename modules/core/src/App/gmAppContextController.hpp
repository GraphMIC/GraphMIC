#pragma once

#include <QObject>

namespace gm
{
    namespace App
    {
        namespace Context
        {
            class Base;
            class Graph;
            class Python;
            class Viewer;
            class Settings;
            
            class Controller : public QObject
            {
                Q_OBJECT
                Q_PROPERTY(gm::App::Context::Base* activeContext READ getActiveContext NOTIFY activeContextChanged);
                Q_PROPERTY(gm::App::Context::Graph* graph READ getGraph CONSTANT);
                Q_PROPERTY(gm::App::Context::Python* python READ getPython CONSTANT);
                Q_PROPERTY(gm::App::Context::Viewer* viewer READ getViewer CONSTANT);
                Q_PROPERTY(gm::App::Context::Settings* settings READ getSettings CONSTANT);
            private:
                Base* m_activeContext;
                Controller();
            public:
                static Controller* instance;
                auto init() -> void;
                auto setActiveContext(Base*) -> void;
                auto getActiveContext() -> Base*;
                auto getGraph() -> Graph*;
                auto getPython() -> Python*;
                auto getViewer() -> Viewer*;
                auto getSettings() -> Settings*;
                static auto Create() -> Controller*;
                ~Controller();
            public slots:
                void setGraphContext();
                void setPythonContext();
                void setViewerContext();
                void setSettingsContext();
            signals:
                void activeContextChanged();
            };
        }
    }
}