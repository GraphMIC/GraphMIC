import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib


Item
{
    id: root;

    anchors.left: parent ? parent.left : undefined;
    anchors.right: parent ? parent.right : undefined;

    property var testCase;
    signal selected();

    height: 24;

    Lib.MouseArea
    {
        anchors.fill: parent;

        onClicked:
        {
            root.selected(testCase);
            testCase.select();
        }
    }

    Lib.IconButton
    {
        id: btnRun;

        anchors.left: parent.left;
        anchors.leftMargin: 8;
        anchors.verticalCenter: parent.verticalCenter;
        type: types.fa_play_circle;
        onClicked: testCase.run();
    }

    Lib.Label
    {
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: btnRun.right;
        anchors.right: icon.left;
        anchors.margins: 4;

        color: testCase.selected ? "#fff" : "#939CAA";

        font.pixelSize: 9;
        text: testCase.imageInfo;
    }

    Lib.IconButton
    {
        id: icon;

        anchors.right: parent.right;
        anchors.rightMargin: 4;
        anchors.verticalCenter: parent.verticalCenter;
        type: testCase.passed ? types.fa_check_circle : types.fa_times_circle;
        color: testCase.passed ? "#00ff00" : "#ff0000"
        visible: testCase.finished;
    }

    Lib.Edge
    {
        align: sides.bottom;
        color: "#272A30"
    }
}
