import QtQuick 2.5

import org.graphmic.app 1.0 as App

MouseArea
{
    property bool debug: App.instance.controllers.debug.debugUI;
    property color col: this.containsMouse ? "#00ff00" : "#ff0000"

    propagateComposedEvents: true;
    hoverEnabled: true;

    onDoubleClicked: { mouse.accepted = true; }

    Rectangle
    {
        anchors.left: parent.left;
        anchors.top: parent.top;
        width: 4;
        height: 1;
        color: parent.col;
        visible: parent.debug;
    }

    Rectangle
    {
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        width: 4;
        height: 1;
        color: parent.col;
        visible: parent.debug;
    }

    Rectangle
    {
        anchors.right: parent.right;
        anchors.top: parent.top;
        width: 4;
        height: 1;
        color: parent.col;
        visible: parent.debug;
    }

    Rectangle
    {
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        width: 4;
        height: 1;
        color: parent.col;
        visible: parent.debug;
    }

    Rectangle
    {
        anchors.left: parent.left;
        anchors.top: parent.top;
        width: 1;
        height: 4;
        color: parent.col;
        visible: parent.debug;
    }

    Rectangle
    {
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        width: 1;
        height: 4;
        color: parent.col;
        visible: parent.debug;
    }

    Rectangle
    {
        anchors.right: parent.right;
        anchors.top: parent.top;
        width: 1;
        height: 4;
        color: parent.col;
        visible: parent.debug;
    }

    Rectangle
    {
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        width: 1;
        height: 4;
        color: parent.col;
        visible: parent.debug;
    }
}
