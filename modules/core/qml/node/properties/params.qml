import QtQuick 2.5
import QtQuick.Controls 1.4

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.core.node.param 1.0 as Param

Column
{
    id: root;

    property var focusView: undefined;

    anchors.left: parent.left;
    anchors.right: parent.right;

    Rectangle
    {
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
            text: "Node Params";
        }

        Lib.Edge { align: sides.top; color: "#17191F"; offset: 1 }
        Lib.Edge { align: sides.top; color: "#283039" }

        Lib.Edge { align: sides.bottom; color: "#17191F"; offset: 1 }
        Lib.Edge { align: sides.bottom; color: "#283039" }
    }

    Column
    {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.margins: 4;

        Repeater
        {
            model: node ? node.groupList : 0

            delegate: Param.Group
            {
                group: model.group;
                focusView: root.focusView;
                isDetail: true;
            }
        }
    }
}
