import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root;

    property var controller: App.instance.controllers.python;
    property var editor: controller.editor;

    height: 20;
    color: "#21252B"

    Lib.Edge { align: sides.bottom; color: "#17191F" }
    Lib.Edge { align: sides.top; color: "#17191F" }

    Lib.Label
    {
        anchors.right: parent.right;
        anchors.rightMargin: 8;
        anchors.verticalCenter: parent.verticalCenter;

        font.bold: true;
        font.pixelSize: 10;
        text: controller.script ? controller.script.path : "";
    }

    Row
    {
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.verticalCenter: parent.verticalCenter;

        Lib.Label
        {
            anchors.verticalCenter: parent.verticalCenter;
            font.bold: true;
            text: "cursor [" + editor.line + ":" + editor.column + "]";
        }
    }
}
