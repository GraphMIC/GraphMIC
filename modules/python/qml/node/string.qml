import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.python.node 1.0 as Node

Node.Item
{
    anchors.leftMargin: 8;
    anchors.rightMargin: 8;

    InputField
    {
        anchors.left: parent.left;
        anchors.right: parent.right;

        label.text: param.name;
        input.text: param.value;
    }
}
