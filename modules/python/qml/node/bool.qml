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
        anchors.right: cb.left;
        anchors.rightMargin: 8;
        anchors.verticalCenter: parent.verticalCenter;
        text: param.name;
        font.pixelSize: 12;
    }

    Lib.CheckBox
    {
        id: cb;

        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
        checked: param.value;
    }
}
