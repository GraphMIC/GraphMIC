#pragma once

#include <QMenu>
#include <QString>
#include <QAction>
#include <QObject>

namespace gm
{
    namespace App
    {
        class Menu : public QObject
        {
            Q_OBJECT
        private:
            auto initMacMenu() -> void;
            auto initWinMenu() -> void;
        public:
            enum ActionID
            {
                FileNewProject,
                FileNewPipeline,
                FileNewPythonScript,
                FileNewDocFile,
                EditUndo,
                EditRedo,
                EditCut,
                EditCopy,
                EditPaste,
                HelpAbout,
                HelpDocs,
                HelpPrefs
            };
        private:
            Menu() = default;
        public:
            static Menu* instance;
            static auto Create() -> Menu*;
            auto addItem(QMenu*, ActionID, const QString&, QString = 0) -> void;
            auto addLine(QMenu*) -> void;
            auto init() -> void;
            ~Menu() = default;
        public slots:
            void onAction(ActionID);
        };
    }
}