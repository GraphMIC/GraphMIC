import QtQuick 2.5
import QtQuick.Controls 1.4

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib


Rectangle
{
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: col.height + 12;

    property alias icon: icon;
    property alias label: label;
    property bool highlight: false;
    property color labelColor: root.highlight || ma.containsMouse ? "#fff" : "#939CAA";
    color: highlight ? "#3C424F" : "#21252B"
    signal clicked();

    Column
    {
        id: col;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;

        spacing: 4;

        Lib.Icon
        {
            id: icon;

            anchors.left: parent.left;
            anchors.right: parent.right;

            pixelSize: 16;

            color: root.labelColor;
        }

        Lib.Label
        {
            id: label;

            anchors.left: parent.left;
            anchors.right: parent.right;

            font.pixelSize: 10;
            font.bold: true;

            styleColor: "#111";
            style: Text.Sunken;
            horizontalAlignment: Text.AlignHCenter;

            color: root.labelColor;
        }
    }

    Lib.MouseArea
    {
        id: ma;

        anchors.fill: parent;

        hoverEnabled: true;

        onClicked: root.clicked();
    }
}
