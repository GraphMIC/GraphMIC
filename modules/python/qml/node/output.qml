import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.python.node 1.0 as Node

Node.Item
{
    id: root;

    property int size: 14;
    property int offset: 10;
    property color bgColor: "#18191d";
    property color okColor: "#939CAA";
    property color errorColor: "#FF4C00"
    property color color: "#939CAA";
    property color labelColor: "#3C424F"
    property color typeColor: param.dataTypeID > 0 ? param.dataTypeID > 1 ? "#0CB8FF" : "#F328FA" : "#fff";
    property bool isDetail: false;
    property bool empty: true;

    height: 24;

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
        text: param.name;
    }

    Item
    {
        id: slotRect;

        width: root.height;
        height: root.height;
        anchors.right: parent.right;
        anchors.rightMargin: -height/2;

        Rectangle
        {
            anchors.centerIn: parent;
            radius: width/2;
            width: root.size;
            height: root.size;
            color: root.bgColor;
            border.color: root.empty ? "#939CAA" : "#fff";
            border.width: 2;

            Rectangle
            {
                anchors.centerIn: parent;
                width: root.size - 8;
                height: root.size - 8;
                radius: width/2;
                visible: !root.empty;
            }
        }
    }

    Lib.Label
    {
        id: label;

        anchors.right: slotRect.left;
        anchors.margins: 6;
        anchors.verticalCenter: parent.verticalCenter;
        text: param.dataTypeString;
        color: root.empty ? "#000" : root.typeColor;
        font.pixelSize: 10;
        font.bold: true;
    }
}
