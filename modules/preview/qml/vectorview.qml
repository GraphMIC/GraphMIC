import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.preview 1.0 as Preview
import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    property var slot;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.margins: 4;

    height: 38;

    Preview.VectorViewer
    {
        id: controller;

        output: root.slot;
    }

    Lib.TabHeader
    {
        id: header;

        anchors.left: parent.left;
        anchors.top: parent.top;
        height: 18;

        Lib.TagLabel
        {
            anchors.verticalCenter: parent.verticalCenter;

            radius: 2;
            color: "#17191F"
            label.color: "#B80CFF"
            label.text: "vector:"
            label.font.pixelSize: 10;
        }

        Lib.Label
        {
            anchors.verticalCenter: parent.verticalCenter;
            text: slot.name;
            font.pixelSize: 10;
            font.bold: true;
            color: "#fff"
        }
    }

    Rectangle
    {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: header.bottom;

        radius: 3;
        height: 20;

        border.color: "#3C424F";
        color: "#21252B";

        Lib.Label
        {
            id: label;

            anchors.fill: parent;
            anchors.margins: 4;

            font.pixelSize: 10;

            text: controller.vector ? (controller.vector.x).toFixed(2) + ", " + (controller.vector.y).toFixed(2) + ", " + (controller.vector.z).toFixed(2) + ", " + (controller.vector.w).toFixed(2) : "n/a"
        }
    }
}
