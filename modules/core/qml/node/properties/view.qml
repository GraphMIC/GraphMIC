import QtQuick 2.5
import QtQuick.Controls 1.4

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.preview 1.0 as Preview

Rectangle
{
    id: root;

    property var focusView;
    property var controller: App.instance.controllers.nodeProperties;
    property var node: controller.node;
    property real alpha: 1;

    clip: true;

    color: "#21252B";

    Lib.MouseArea
    {
        id: ma;

        anchors.fill: parent;
        hoverEnabled: true;
        propagateComposedEvents: false;
        onPressed: root.forceActiveFocus();
    }

    Rectangle
    {
        id: header;

        anchors.left: parent.left;
        anchors.right: parent.right;

        height: 24;
        color: "#121417"

        Lib.Label
        {
            anchors.left: parent.left;
            anchors.leftMargin: 6;
            anchors.verticalCenter: parent.verticalCenter;

            font.bold: true;
            font.pixelSize: 11;
            color: "#fff"
            text: "Node Outputs";
        }

        Preview.Navigator
        {
            anchors.right: parent.right;
            anchors.rightMargin: 6;
            anchors.verticalCenter: parent.verticalCenter;
        }

        Lib.Edge { align: sides.bottom; color: "#17191F"; offset: 1 }
        Lib.Edge { align: sides.bottom; color: "#283039" }
    }

    Lib.ScrollView
    {
        id: scrollView;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: parent.bottom;

        Column
        {
            width: root.width
            y: 4;

            Preview.View
            {
                id: preview;

                anchors.left: parent.left;
                anchors.right: parent.right;
            }

            Params
            {
                focusView: root.focusView;
            }
        }
    }
}
