import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    default property alias content: container.children;
    property var param;

    anchors.left: parent.left;
    anchors.right: parent.right;
    height: 30;

    Rectangle
    {
        id: selBox;

        anchors.fill: parent;

        anchors.leftMargin: - parent.anchors.leftMargin;
        anchors.rightMargin: - parent.anchors.rightMargin;

        color: "#00000000"
        border.color: param.selected ? "#3385ff" : "#00000000"
    }

    Item
    {
        id: container;

        anchors.fill: parent;
    }

    MouseArea
    {
        id: ma;

        anchors.fill: parent;
        onClicked: param.select();
        drag.target: parent;
    }

    Lib.IconButton
    {
        anchors.left: selBox.right;
        anchors.leftMargin: 8;
        anchors.verticalCenter: parent.verticalCenter;
        type: types.fa_times_circle;
        visible: param.selected;
        onClicked: param.remove();
    }
}
