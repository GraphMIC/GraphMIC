import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    property var testCases;
    property var testUnit;

    Rectangle
    {
        id: header;

        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 24;

        color: "#131518"

        Lib.Label
        {
            id: label;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.margins: 4;
            text: "Test Cases";
        }

        Lib.IconButton
        {
            anchors.verticalCenter: parent.verticalCenter;
            anchors.right: parent.right;
            anchors.rightMargin: 4;

            visible: root.testUnit != undefined;
            type: root.testUnit && root.testUnit.running ? types.fa_times_circle : types.fa_play_circle;
            colorNormal:  root.testUnit && root.testUnit.running ? "#ff0000" : "#939CAA";

            onClicked:
            {
                root.testUnit.runThreaded();
            }
        }
    }

    Lib.ListView
    {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: outputView.top;

        clip: true;

        model: root.testCases;
        delegate: CaseView
        {
            testCase: model.modelData;

            onSelected:
            {
                outputView.text = testCase.output;
            }
        }
    }

    OutputView
    {
        id: outputView;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
    }

    Lib.Edge { align: sides.left; color: "#3C424F" }

    function showUnit(unit) {
        root.testUnit = unit;
        root.testCases = unit.cases;
        label.text = "Test Cases [" + testCases.length + "]";
    }
}
