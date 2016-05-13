import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.preview 1.0 as Preview
import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    property var slot;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.margins: 4;

    height: header.height + body.height;

    Preview.PointsetViewer
    {
        id: controller;

        output: root.slot;
    }

    Lib.TabHeader
    {
        id: header;

        anchors.left: parent.left;
        anchors.top: parent.top;
        height: 18;

        Lib.TagLabel
        {
            anchors.verticalCenter: parent.verticalCenter;

            radius: 2;
            color: "#17191F"
            label.color: "#0CFFB8"
            label.text: "pointset";
            label.font.pixelSize: 10;
        }

        Lib.Label
        {
            anchors.verticalCenter: parent.verticalCenter;
            text: controller.pointset ? slot.name + " [" + controller.pointset.size + "]" : slot.name;
            font.pixelSize: 10;
            font.bold: true;
            color: "#fff"
        }
    }

    Rectangle
    {
        anchors.fill: body;

        radius: 3;
        height: 20;

        border.color: "#3C424F";
        color: "#21252B";
    }

    Column
    {
        id: body;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: header.bottom;

        Lib.Label
        {
            anchors.left: parent.left;
            anchors.right: parent.right;

            visible: !controller.pointset;
            height: 20;

            text: "n/a";
        }

        Lib.ListView
        {
            id: listview;

            anchors.left: parent.left;
            anchors.right: parent.right;

            height: 200;
            clip: true;
            visible: controller.pointset;

            model: controller.pointset ? controller.pointset.points : 0;
            delegate: Item
            {
                anchors.left: parent.left;
                anchors.right: parent.right;

                height: 20;

                Lib.TagLabel
                {
                    anchors.left: parent.left;
                    anchors.leftMargin: 4;
                    anchors.verticalCenter: parent.verticalCenter;

                    border.color: "#3C424F"
                    color: "#17191F"
                    label.text: index;
                    label.font.pixelSize: 10;
                    label.color: "#939CAA"
                }

                Lib.Label
                {
                    anchors.centerIn: parent;
                    text: model.x + ", " + model.y + ", " + model.z
                }

                Rectangle
                {
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    anchors.bottom: parent.bottom;

                    height: 1;
                    color: "#283039"
                }
            }
        }
    }
}
