import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root;

    property alias label: label;
    property alias input: input;

    anchors.verticalCenter: parent.verticalCenter;

    height: input.height + 6;
    radius: 2;
    clip: true;
    color: "#131518";
    border.color: "#939CAA";

    Lib.Label
    {
        id: label;

        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.top: input.top;
        anchors.right: input.left;
        anchors.rightMargin: 4;
        font.pixelSize: 12;
    }

    Lib.Label
    {
        id: input;

        clip: true;

        anchors.right: parent.right;
        anchors.rightMargin: 6;
        anchors.verticalCenter: parent.verticalCenter;

        color: "#fff"
    }
}
