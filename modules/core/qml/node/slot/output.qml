import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    property var slot;
    property int size: 14;
    property int offset: 10;
    property color bgColor: "#18191d";
    property color okColor: "#939CAA";
    property color errorColor: "#FF4C00"
    property color color: "#939CAA";
    property color labelColor: "#3C424F"
    property color typeColor: slot.dataType > 0 ? slot.dataType > 1 ? "#0CB8FF" : "#F328FA" : "#fff";
    property bool isDetail: false;

    anchors.right: parent.right;

    height: 24;
    width: labelView.width;

    Item
    {
        id: labelView;

        width: label.width + 26;
        height: root.size;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        clip: true;

        Rectangle
        {
            anchors.fill: parent;
            radius: 10;
            anchors.rightMargin: -height/2;
            color: root.labelColor;
            border.color: root.labelColor;
        }

        Rectangle
        {
            radius: width/2;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.right: parent.right;
            anchors.rightMargin: -height/2;
            width: root.size + root.offset;
            height: root.size + root.offset;
            color: root.bgColor;
            border.color: root.labelColor;
        }
    }

    Lib.Label
    {
        id: title;

        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: labelView.left;
        anchors.margins: 6;
        font.pixelSize: 10;
        // text: slot.name + " [" + slot.dataSize + "]";
        // text: slot.data ? slot.data.count : "none";
        text: slot.name + " . " + slot.dataCount;
    }

    Item
    {
        id: slotRect;

        width: root.height;
        height: root.height;
        anchors.right: parent.right;
        anchors.rightMargin: -height/2;

        DropArea
        {
            anchors.fill: parent;

            onDropped: slot.connect(drag.source.slot);
        }

        Item
        {
            id: ghost;

            width: parent.width;
            height: parent.height;

            onXChanged: slot.moveConnectX(x);
            onYChanged: slot.moveConnectY(y);

            Drag.active: ma.drag.active;
            Drag.hotSpot.x: width/2;
            Drag.hotSpot.y: height/2;

            property var slot: root.slot;

            Lib.MouseArea
            {
                id: ma;

                anchors.fill: parent;
                drag.target: parent;
                hoverEnabled: true;
                drag.smoothed: false;
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onPressed:
                {
                    if (mouse.button == Qt.LeftButton)
                    {
                        slot.connecting = true;
                    }
                }

                onClicked:
                {
                    if (mouse.button == Qt.RightButton)
                    {
                        slot.disconnect();
                    }
                }

                onReleased:
                {
                    slot.connecting = false;
                    ghost.Drag.drop();
                    parent.x = 0;
                    parent.y = 0;
                }
            }
        }

        Rectangle
        {
            anchors.centerIn: parent;
            radius: width/2;
            width: root.size;
            height: root.size;
            color: root.bgColor;
            border.color: slot.empty ? "#939CAA" : "#fff";
            border.width: 2;

            Rectangle
            {
                anchors.centerIn: parent;
                width: root.size - 8;
                height: root.size - 8;
                radius: width/2;
                visible: !slot.empty;
            }
        }
    }

    Lib.Label
    {
        id: label;

        anchors.right: slotRect.left;
        anchors.margins: 6;
        anchors.verticalCenter: parent.verticalCenter;
        text: slot.dataTypeString;
        color: slot.empty ? "#000" : root.typeColor;
        font.pixelSize: 10;
        font.bold: true;
    }
}
