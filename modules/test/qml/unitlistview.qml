import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.app 1.0 as App

Item
{
    id: root;

    property var units;
    property var caseList;

    property var controller: App.instance.controllers.test

    Rectangle
    {
        id: header;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;

        height: 24;

        color: "#131518"

        Lib.Label
        {
            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.margins: 4;
            text: "Test Units [" + units.length + "]"
        }

        Lib.IconButton
        {
            anchors.verticalCenter: parent.verticalCenter;
            anchors.right: parent.right;
            anchors.rightMargin: 4;

            visible: !controller.loading;
            type: controller.running ? types.fa_times_circle : types.fa_play_circle;
            colorNormal:  controller.running ? "#ff0000" : "#939CAA";

            onClicked: controller.runUnits();
        }
    }

    Lib.ListView
    {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: parent.bottom;

        clip: true;

        model: root.units;
        delegate: UnitView
        {
            testUnit: model.modelData;
            caseListView: root.caseList;
        }
    }
}
