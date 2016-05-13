#include "gmLog.hpp"
#include "gmIOPath.hpp"
#include "gmAppMenu.hpp"
#include "gmAppController.hpp"
#include "gmDialogController.hpp"

#include <QMenuBar>

namespace gm
{
    namespace App
    {
        Menu* Menu::instance = nullptr;
        
        auto Menu::init() -> void
        {
            log_trace(Log::Func);
            
            if (instance)
            {
                throw "instance already existing";
            }
            
            instance = this;
            
#ifdef Q_OS_DARWIN
            initMacMenu();
#else
            initWinMenu();
#endif
        }
        
        auto Menu::Create() -> Menu*
        {
            log_trace(Log::Func);
            
            return new Menu();
        }
        
        auto Menu::initWinMenu() -> void
        {
            log_trace(Log::Func);
        }
        
        auto Menu::addItem(QMenu* parent, ActionID action, const QString& title, QString shortcut) -> void
        {
            log_trace(Log::Func);
            
            auto item = parent->addAction(title);
            item->setShortcut(shortcut);
            QObject::connect(item, &QAction::triggered, [=](void) { this->onAction(action); });
        }
        
        auto Menu::addLine(QMenu* menu) -> void
        {
            log_trace(Log::Func);
            
            menu->addSeparator();
        }
        
        auto Menu::initMacMenu() -> void
        {
            log_trace(Log::Func);
            
            auto menuBar        = new QMenuBar(0);
            auto editMenu		= new QMenu(tr("Edit"), menuBar);
            auto helpMenu		= new QMenu(tr("Help"), menuBar);
            
            addItem(editMenu, EditUndo, "Undo", "Ctrl+Z");
            addItem(editMenu, EditRedo, "Redo", "Ctrl+Shift+Z");
            addLine(editMenu);
            addItem(editMenu, EditCut, "Cut", "Ctrl+X");
            addItem(editMenu, EditCopy, "Copy", "Ctrl+C");
            addItem(editMenu, EditPaste, "Paste", "Ctrl+V");
            
            addItem(helpMenu, HelpAbout, "About");
            addItem(helpMenu, HelpDocs, "Documentation");
            addItem(helpMenu, HelpPrefs, "Preferences...");
            
            menuBar->addMenu(editMenu);
            menuBar->addMenu(helpMenu);
        }
        
        auto Menu::onAction(ActionID id) -> void
        {
            log_trace(Log::Func);
            
            switch (id)
            {
                case HelpAbout:
                    Dialog::Controller::instance->showAbout();
                    break;
                case HelpPrefs:
                    Dialog::Controller::instance->showSettings();
                default:
                    break;
            }
        }
    }
}