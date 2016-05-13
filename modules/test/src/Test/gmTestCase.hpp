#pragma once

#include <QVariantMap>
#include <QObject>
#include <QHash>

namespace gm
{
    namespace Node
    {
        class Object;
    }

    namespace Slot
    {
        class InputBase;
    }

    namespace Test
    {
        class Unit;

        class Case : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString imageInfo READ getImageInfo NOTIFY imageInfoChanged);
            Q_PROPERTY(QString output READ getOutput NOTIFY outputChanged);
            Q_PROPERTY(bool finished READ getFinished NOTIFY finishedChanged);
            Q_PROPERTY(bool selected READ isSelected NOTIFY selectedChanged);
            Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged);
            Q_PROPERTY(bool passed READ getPassed NOTIFY passedChanged);
            Q_PROPERTY(bool pass READ getPass CONSTANT);
            Q_PROPERTY(int number READ getNumber CONSTANT);
        private:
            QHash<Slot::InputBase*, QStringList> m_imageRefMap;
            QVariantMap m_attributeMap;
            Node::Object* m_node = nullptr;
            QString m_imageInfo;
            Unit* m_testUnit;
            QString m_output;
            bool m_finished = false;
            bool m_selected = false;
            bool m_running = false;
            bool m_passed = false;
            bool m_pass = true;
            int m_number = 0;
        private:
            Case();
            auto applyAttributes() -> void;
            auto initImageReferences() -> void;
            auto getNumber() -> int;
        public:
            static auto FromJson(QJsonValue) -> Case*;
            auto addImageInfo(const QString&) -> void;
            auto getImageInfo() -> QString;
            auto setTestUnit(Unit*) -> void;
            auto setOutput(const QString&) -> void;
            auto getOutput() -> QString;
            auto setFinished(bool) -> void;
            auto getFinished() -> bool;
            auto getPass() -> bool;
            auto getDimension() -> int;
            auto getPixelString() -> QString;
            auto getComponentString() -> QString;
            auto setNode(Node::Object*) -> void;
            auto setRunning(bool) -> void;
            auto isRunning() -> bool;
            auto setPassed(bool) -> void;
            auto getPassed() -> bool;
            auto setNumber(int) -> void;
            auto setSelected(bool) -> void;
            auto isSelected() -> bool;
            auto init() -> void;
        public slots:
            void run();
            void select();
        signals:
            void imageInfoChanged();
            void selectedChanged();
            void finishedChanged();
            void runningChanged();
            void outputChanged();
            void passedChanged();
        };
    }
}