import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: header;

    anchors.left: parent.left;
    anchors.right: parent.right;

    property alias title: label.text;

    height: 24;
    color: "#121417"

    Lib.Label
    {
        id: label;

        anchors.left: parent.left;
        anchors.leftMargin: 6;
        anchors.verticalCenter: parent.verticalCenter;

        font.bold: true;
        font.pixelSize: 11;
        color: "#fff"
        text: "Node Preview";
    }

    Lib.Edge { align: sides.bottom; color: "#17191F"; offset: 1 }
    Lib.Edge { align: sides.bottom; color: "#283039" }
}
