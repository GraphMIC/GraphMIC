#pragma once

#include "gmViewerExport.hpp"

#include <mitkLevelWindowManager.h>
#include <mitkDataStorage.h>

#include <QQuickPaintedItem>

namespace gm
{
    namespace ViewItem
    {
        class GM_VIEWER_EXPORT SliderLevelWindowItem: public QQuickPaintedItem
        {
            Q_OBJECT
            Q_PROPERTY(QColor color READ color WRITE setColor)
            Q_PROPERTY(QColor fontColor READ fontColor WRITE setFontColor)
            Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
            Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize)
            Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
            Q_PROPERTY(int level READ getLevel WRITE setLevel NOTIFY levelChanged)
            Q_PROPERTY(int window READ getWindow WRITE setWindow NOTIFY windowChanged)
        private:
            static mitk::DataStorage::Pointer storage;
            QColor  m_color;
            QColor  m_borderColor;
            QColor  m_fontColor;
            QFont   m_font;
            QRect   m_rect;
            QPoint  m_startPos;
            QRect   m_lowerBound;
            QRect   m_upperBound;
            bool m_enabled;
            bool m_resize;
            bool m_bottom;
            bool m_mouseDown;
            bool m_leftbutton;
            bool m_ctrlPressed;
            bool m_scaleVisible;
            bool m_isObserverTagSet;
            int m_fontSize;
            int m_moveHeight;
            int m_level;
            int m_window;
            unsigned long m_observerTag;
            mitk::LevelWindow                 m_LevelWindow;
            mitk::LevelWindowManager::Pointer m_Manager;
        public:
            static SliderLevelWindowItem* instance;
        public:
            SliderLevelWindowItem(QQuickPaintedItem *parent = nullptr);
            ~SliderLevelWindowItem();
            auto setLevelWindowManager(mitk::LevelWindowManager *levelWindowManager) -> void;
            auto getManager() -> mitk::LevelWindowManager*;
            auto color() -> QColor const;
            auto fontColor() -> QColor const;
            auto borderColor() -> QColor const;
            auto setColor(const QColor &color) -> void;
            auto setFontColor(const QColor &color) -> void;
            auto setBorderColor(const QColor &color) -> void;
            auto setLevel(int level) -> void;
            auto setWindow(int window) -> void;
            auto getWindow() -> int;
            auto getLevel() -> int;
            auto fontSize() -> int const;
            auto setFontSize(const int &fontSize) -> void;
            auto isEnabled() -> bool;
            auto setEnabled(bool enable) -> void;
            auto paint(QPainter *painter) -> void override;
            auto mouseMoveEvent(QMouseEvent *mouseEvent) -> void override;
            auto mousePressEvent(QMouseEvent *mouseEvent) -> void override;
            auto mouseReleaseEvent(QMouseEvent *mouseEvent) -> void override;
            auto hoverMoveEvent(QHoverEvent *event) -> void override;
            auto geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) -> void override;
            void onPropertyModified(const itk::EventObject &e);
            virtual auto update() -> void;
            static auto SetDataStorage(mitk::DataStorage *ds) -> void;
        public slots:
            void hideScale();
            void showScale();
        signals:
            void enabledChanged();
            void levelChanged();
            void windowChanged();
            void sync();
        };
    }
}
