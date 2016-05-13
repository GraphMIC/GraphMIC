#pragma once

#include <QObject>

namespace gm
{
    namespace Connection
    {
        class View;
    }
    
    namespace Node
    {
        class Connector : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(bool active READ getActive WRITE setActive NOTIFY activeChanged);
            Q_PROPERTY(int x1 READ getX1 WRITE setX1 NOTIFY x1Changed);
            Q_PROPERTY(int y1 READ getY1 WRITE setY1 NOTIFY y1Changed);
            Q_PROPERTY(int x2 READ getX2 WRITE setX2 NOTIFY x2Changed);
            Q_PROPERTY(int y2 READ getY2 WRITE setY2 NOTIFY y2Changed);
        private:
            Connection::View* m_view;
            bool m_active = false;
            int m_x1 = 0;
            int m_y1 = 0;
            int m_x2 = 0;
            int m_y2 = 0;
        public:
            static Connector* instance;
            Connector();
            auto setView(Connection::View*) -> void;
            auto getView() -> Connection::View*;
            auto setActive(bool) -> void;
            auto getActive() -> bool;
            auto setX1(int) -> void;
            auto getX1() -> int;
            auto setY1(int) -> void;
            auto getY1() -> int;
            auto setX2(int) -> void;
            auto getX2() -> int;
            auto setY2(int) -> void;
            auto getY2() -> int;
            auto updateView() -> void;
            ~Connector();
        signals:
            void activeChanged();
            void x1Changed();
            void y1Changed();
            void x2Changed();
            void y2Changed();
        };
    }
}