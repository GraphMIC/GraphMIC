import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.python.node 1.0 as Node

Node.Item
{
    anchors.leftMargin: 8;
    anchors.rightMargin: 8;

    Lib.Label
    {
        id: label;

        anchors.left: parent.left;
        anchors.right: dropdown.left;
        anchors.rightMargin: 8;
        anchors.verticalCenter: parent.verticalCenter;
        text: param.name;
        font.pixelSize: 12;
    }

    Lib.DropDown
    {
        id: dropdown;

        anchors.right: parent.right;
        anchors.leftMargin: 4;
        anchors.verticalCenter: parent.verticalCenter;

        model: param.options;
        currentIndex: param.index;

        property var activeIndex: param.index;

        onActiveIndexChanged: currentIndex = activeIndex;
    }
}
