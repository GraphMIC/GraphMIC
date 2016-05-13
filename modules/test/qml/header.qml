import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.app 1.0 as App

Item
{
    id: header;

    property var controller: App.instance.controllers.test;

    height: 32;

    Row
    {
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        spacing: 4;
        anchors.leftMargin: 4;

        Lib.Label
        {
            anchors.verticalCenter: parent.verticalCenter;

            font.bold: true;
            font.pixelSize: 11;
            text: "Testing";
        }
    }

    Lib.Label
    {
        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        anchors.rightMargin: 4;

        font.bold: true;
        color: controller.loading ? "#3385ff" : "#00ff00";
        text: controller.stateString;
    }

    Lib.Edge { align: sides.bottom; color: "#17191F"; offset: 1 }
    Lib.Edge { align: sides.bottom; color: "#283039" }
}
