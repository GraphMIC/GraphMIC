import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root;

    property bool toggle: false;
    property bool checked: false;
    property alias label: label;
    property color baseColor: "#31363E"
    property color styleColor: (ma.pressed || checked) ? "#0CB8FF" : ma.containsMouse ? "#343942" : baseColor;

    width: label.width + 32;
    height: label.height + 8;
    color: root.styleColor;
    border.color: "#1E1E1E"
    radius: 2

    signal clicked();

    Behavior on styleColor
    {
        ColorAnimation
        {
            duration: 30;
        }
    }

    Lib.Label
    {
        id: label;

        anchors.centerIn: parent;
        color: root.enabled ? (ma.containsMouse || root.checked)  ? "#FFF" : "#939CAA" : "#666";
        text: "Button"
    }

    Lib.MouseArea
    {
        id: ma;

        anchors.fill: parent;
        hoverEnabled: true;

        onClicked:
        {
            if (root.toggle)
            root.checked = ! root.checked;

            root.clicked();
        }
    }
}
