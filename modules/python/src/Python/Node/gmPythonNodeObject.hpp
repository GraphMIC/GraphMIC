#pragma once

#include <QObject>
#include <QQmlListProperty>

namespace gm
{
    namespace Python
    {
        class Script;

        namespace Node
        {
            class Input;
            class Output;
            class Param;
            class Component;

            class Object : public QObject
            {
                Q_OBJECT
                Q_PROPERTY(QQmlListProperty<gm::Python::Node::Input> inputs READ getInputList NOTIFY inputsChanged);
                Q_PROPERTY(QQmlListProperty<gm::Python::Node::Output> outputs READ getOutputList NOTIFY outputsChanged);
                Q_PROPERTY(QQmlListProperty<gm::Python::Node::Param> params READ getParamList NOTIFY paramsChanged);
                Q_PROPERTY(gm::Python::Node::Component* selected READ getSelected NOTIFY selectedChanged);
                Q_PROPERTY(QString docLink READ getDocLink WRITE setDocLink NOTIFY docLinkChanged);
                Q_PROPERTY(QString author READ getAuthor WRITE setAuthor NOTIFY authorChanged);
                Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
                Q_PROPERTY(int versionMajor READ getVersionMajor WRITE setVersionMajor NOTIFY versionMajorChanged);
                Q_PROPERTY(int versionMinor READ getVersionMinor WRITE setVersionMinor NOTIFY versionMinorChanged);
                Q_PROPERTY(int versionPatch READ getVersionPatch WRITE setVersionPatch NOTIFY versionPatchChanged);
                Q_PROPERTY(bool forceExecution READ getForceExecution WRITE setForceExecution NOTIFY forceExecutionChanged);
                Q_PROPERTY(bool runnable READ isRunnable WRITE setRunnable NOTIFY runnableChanged);
            private:
                QList<Input*> m_inputs;
                QList<Output*> m_outputs;
                QList<Param*> m_params;
                QString m_docLink;
                QString m_author;
                QString m_name;
                Component* m_selected;
                bool m_forceExecution;
                bool m_runnable;
                int m_versionMajor;
                int m_versionMinor;
                int m_versionPatch;
                Script* m_script;
            public:
                Object() = delete;
                Object(Script* script);
                auto getScript() -> Script*;
                auto getInputList() -> QQmlListProperty<Input>;
                auto getOutputList() -> QQmlListProperty<Output>;
                auto getParamList() -> QQmlListProperty<Param>;
                auto getInputs() -> QList<Input*>;
                auto getOutputs() -> QList<Output*>;
                auto getParams() -> QList<Param*>;
                auto setForceExecution(bool) -> void;
                auto getForceExecution() -> bool;
                auto setRunnable(bool) -> void;
                auto isRunnable() -> bool;
                auto setDocLink(const QString&) -> void;
                auto getDocLink() -> QString;
                auto setAuthor(const QString&) -> void;
                auto getAuthor() -> QString;
                auto setName(const QString&) -> void;
                auto getName() -> QString;
                auto setVersionMajor(int) -> void;
                auto getVersionMajor() -> int;
                auto setVersionMinor(int) -> void;
                auto getVersionMinor() -> int;
                auto setVersionPatch(int) -> void;
                auto getVersionPatch() -> int;
                auto setSelected(Component*) -> void;
                auto getSelected() -> Component*;
                auto deleteInput(Input*) -> void;
                auto deleteOutput(Output*) -> void;
                auto deleteParam(Param*) -> void;
            public slots:
                void addInput();
                void addOutput();
                void addNumberParam();
                void addVectorParam();
                void addStringParam();
                void addOptionParam();
                void addBoolParam();
                void addDirParam();
                void addFilesParam();
                void create();
                void clearSelection();
            signals:
                void forceExecutionChanged();
                void versionMajorChanged();
                void versionMinorChanged();
                void versionPatchChanged();
                void selectedChanged();
                void runnableChanged();
                void docLinkChanged();
                void outputsChanged();
                void inputsChanged();
                void paramsChanged();
                void authorChanged();
                void nameChanged();
            };
        }
    }
}