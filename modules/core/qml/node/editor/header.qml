import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root;

    property var controller: App.instance.controllers.nodeEditor;

    height: 32;
    color: "#21252B"

    Lib.Edge { align: sides.bottom; color: "#17191F" }

    Row
    {
        height: parent.height;
        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: 4;
        spacing: 4;

        Icon
        {
            anchors.verticalCenter: parent.verticalCenter;
            label.text: "Execute"
            enabled: controller.graph;
            onClicked: controller.graph.execute();
        }

        Icon
        {
            anchors.verticalCenter: parent.verticalCenter;
            label.text: "Analyze";
            enabled: controller.graph;
            icon.type: icon.types.fa_gear;
        }
    }

    Lib.IconButton
    {
        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        anchors.rightMargin: 8;

        colorActive: "#ff0000"
        type: types.fa_magnet;
        highlight: controller.snap;

        onClicked: controller.snap = !controller.snap;
    }
}
