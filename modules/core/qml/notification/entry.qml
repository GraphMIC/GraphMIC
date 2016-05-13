import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib


Rectangle
{
    id: rect;

    property var entry;

    width: 430
    height: label.height + 8;

    radius: 3;
    color: "#17191F"
    border.color: ma.containsMouse ? "#939CAA" : "#6C7480"

    Lib.Label
    {
        id: label;

        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.top: parent.top;
        anchors.topMargin: 4;

        width: 400;
        elide: Text.ElideNone;
        wrapMode: Text.WordWrap;
        text: entry.info;
        color: "#fff"
    }

    Lib.Icon
    {
        id: btn;

        anchors.right: parent.right;
        anchors.rightMargin: 4;
        anchors.top: label.top;

        type: entry.type < 2 ? types.fa_exclamation_circle : types.fa_info_circle;
        color: entry.type == 0 ? "#ff9933" : entry.type == 1 ? "#ff0000" : "#095597"
    }

    Lib.MouseArea
    {
        id: ma;

        anchors.fill: parent;

        onClicked:
        {
            if (entry.node)
            {
                entry.node.centerView();
            }
        }
    }
}
