import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Item
{
    property var param;
    property var focusView;
    property bool isDetail: false;

    height: 30;

    Lib.Label
    {
        id: label;

        anchors.left: parent.left;
        anchors.right: cb.left;
        anchors.rightMargin: 8;
        anchors.verticalCenter: parent.verticalCenter;
        text: param.name;
        font.pixelSize: root.isDetail ? 10 : 12;
    }

    Lib.CheckBox
    {
        id: cb;

        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
        checked: param.value;

        onClicked: param.value = !param.value;
    }
}
