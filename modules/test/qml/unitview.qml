import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;


    property var caseListView;
    property var testUnit;

    height: 24;

    Lib.MouseArea
    {
        anchors.fill: parent;
        onClicked:
        {
            testUnit.activate();
            caseListView.showUnit(testUnit);
        }

        onDoubleClicked:
        {
            testUnit.moveToNode();
        }
    }

    Lib.IconButton
    {
        id: btnRun;

        anchors.left: parent.left;
        anchors.leftMargin: 8;
        anchors.verticalCenter: parent.verticalCenter;
        type: types.fa_play_circle;
        visible: !testUnit.running;

        onClicked:
        {
            testUnit.activate();
            caseListView.showUnit(testUnit);
            testUnit.runThreaded();
        }
    }

    Lib.IconButton
    {
        anchors.centerIn: btnRun;
        visible: testUnit.running;
        type: types.fa_refresh;
        color: "#ff5511"

        RotationAnimator on rotation {
            duration: 800
            loops: Animation.Infinite
            from: 0
            to: 360
            running: testUnit.running;
        }
    }

    Lib.Label
    {
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: btnRun.right;
        anchors.right: results.left;
        anchors.margins: 4;

        font.pixelSize: 11;
        color: testUnit.active ? "#fff" : "#939CAA"
        font.bold: true;

        text: testUnit.prefix + "::" + testUnit.name
    }

    UnitResultView
    {
        id: results;

        testUnit: root.testUnit;

        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        anchors.rightMargin: 4;
    }
/*
    Row
    {
        id: row;

        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        anchors.rightMargin: 4;

        spacing: 4;

        Lib.Label
        {
            anchors.verticalCenter: parent.verticalCenter;

            text: testUnit.cases.length;
            font.pixelSize: 10;
        }

        Lib.Label
        {
            anchors.verticalCenter: parent.verticalCenter;

            text: testUnit.passedCount;
            color: "#00ff00";
            font.pixelSize: 10;
        }

        Lib.Label
        {
            anchors.verticalCenter: parent.verticalCenter;

            text: testUnit.failedCount;
            color: "#ff0000";
            font.pixelSize: 10;
        }
    }
*/

    Lib.Edge
    {
        align: sides.bottom;
        color: "#272A30"
    }
}
