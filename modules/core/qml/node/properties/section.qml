import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Column
{
    id: root;

    property alias label: label;
    property alias header: header;
    property alias separator: separator;
    property color color: "#21252B"

    anchors.left: parent.left;
    anchors.right: parent.right;

    Rectangle
    {
        id: header;

        anchors.left: parent.left;
        anchors.right: parent.right;

        height: label.height + 6;
        color: root.color;

        Lib.Label
        {
            id: label;

            anchors.left: parent.left;
            anchors.leftMargin: 6;
            anchors.verticalCenter: parent.verticalCenter;

            font.bold: true;
            font.pixelSize: 11;
            color: "#fff"
            text: "<label>";
        }

        Rectangle
        {
            id: separator;

            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;

            height: 1;
            color: "#283039" 
        }
    }
}
