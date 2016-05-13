import QtQuick 2.5

import org.graphmic.core.node.editor 1.0 as NodeEditor
import org.graphmic.app 1.0 as App
import org.graphmic.viewer 1.0 as Viewer
import org.graphmic.python 1.0 as Python

Item
{
    id: root;

    property var context: App.instance.controllers.context;

    NodeEditor.View
    {
        id: nodeEditor;

        anchors.fill: parent;
        visible: context.graph.visible;
        enabled: visible;
    }

    Python.View
    {
        anchors.fill: parent;
        color: "#282C34"
        visible: context.python.visible;
        enabled: visible;
    }

    Viewer.View
    {
        anchors.fill: parent;
        visible: context.viewer.visible;
        enabled: visible;
    }

    Rectangle
    {
        anchors.fill: parent;
        color: "#282C34"
        visible: context.settings.visible;
        enabled: visible;
    }

    Component.onCompleted:
    {
        nodeEditor.activate();
    }
}
