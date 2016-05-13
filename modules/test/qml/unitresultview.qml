import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Row
{
    property var testUnit;

    spacing: 4;

    Lib.Label
    {
        anchors.verticalCenter: parent.verticalCenter;
        text: testUnit.cases.length;
    }

    Rectangle
    {
        width: 45;

        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.margins: 4;

        radius: 2;

        color: testUnit.passedCount > 0 ? "#00ff00" : "#444";

        Lib.Icon
        {
            id: icPass;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            pixelSize: 10;

            color: "#21252B"
            type: types.fa_check;
        }

        Rectangle
        {
            anchors.left: icPass.right;
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            anchors.margins: 1;
            anchors.leftMargin: 4;

            radius: 2;
            color: "#21252B"

            Lib.Label
            {
                anchors.centerIn: parent;

                font.pixelSize: 11;
                font.bold: true;
                text: testUnit.passedCount;
            }
        }
    }

    Rectangle
    {
        width: 45;

        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.margins: 4;

        color: testUnit.failedCount > 0 ? "#ff0000" : "#444";

        Lib.Icon
        {
            id: icFail;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            pixelSize: 10;

            color: "#21252B"
            type: types.fa_times;
        }

        Rectangle
        {
            anchors.left: icFail.right;
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            anchors.margins: 1;
            anchors.leftMargin: 4;

            radius: 2;
            color: "#21252B"

            Lib.Label
            {
                anchors.centerIn: parent;

                font.pixelSize: 11;
                font.bold: true;
                text: testUnit.failedCount;
            }
        }
    }
}
