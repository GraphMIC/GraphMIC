import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.leftMargin: 4;
    anchors.rightMargin: 4;

    property alias checkbox: checkbox;
    property alias label: label;

    signal clicked();

    height: 24

    Lib.Label
    {
        id: label;

        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        width: 80;
        text: "value";
        color: "#fff"
    }

    Lib.CheckBox
    {
        id: checkbox;

        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
        checked: param.value;

        onClicked: root.clicked();
    }
}
