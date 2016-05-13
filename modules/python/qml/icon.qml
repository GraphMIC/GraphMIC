import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    property alias label: label;
    property alias icon: icon;

    signal clicked();

    width: row.width + 12;
    height: icon.height + 6;
    radius: 4;

    border.color: "#29313A"
    color: "#00000000"

    Row
    {
        id: row;

        spacing: 4;
        anchors.centerIn: parent;

        Lib.Label
        {
            id: label;

            text: "<title>"
            font.bold: true;
            font.pixelSize: 10;
            color: ma.containsMouse ? "#fff" : "#939CAA";
        }

        Lib.Icon
        {
            id: icon;

            anchors.verticalCenter: parent.verticalCenter;

            type: types.fa_play_circle_o;
            color: ma.containsMouse ? "#fff" : "#939CAA";
        }
    }

    Lib.MouseArea
    {
        id: ma;

        anchors.fill: parent;
        onClicked: parent.clicked();
    }
}
