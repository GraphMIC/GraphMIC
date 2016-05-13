import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root;
    
    radius: 3;
    width: 140;
    height: col.height + 10
    color: "#bb111111";
    border.color: "#fff"

    property var slot;

    Column
    {
        id: col;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.centerIn: parent;

        Lib.Label
        {
            width: root.width;

            text: slot.name + " [" + slot.dataCount + "]";
        }

        Repeater
        {
            model: slot.dataList;
            delegate: DataView
            {
                dataObject: model.data;
            }
        }
    }

    Behavior on opacity
    {
        NumberAnimation
        {
            duration: 180;
        }
    }
}
