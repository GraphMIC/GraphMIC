import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Item
{
    height: 20;
    property var match;
    property var search;

    Lib.Label
    {
        anchors.left: parent.left;
        anchors.right: row.left;
        anchors.verticalCenter: parent.verticalCenter;

        text: match.name;
        color: "#fff";
    }

    Row
    {
        id: row;

        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;

        Lib.TagLabel
        {
            color: "#000"
            border.color: "#0CB8FF"
            label.text: match.prefix;
            label.font.bold: false;
            radius: 4;
        }
    }

    Lib.MouseArea
    {
        anchors.fill: parent;
        onClicked: input.text = match.name;
    }

    Lib.Edge { align: sides.bottom; color: "#3C4049"; }
}
