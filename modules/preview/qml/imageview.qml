import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.preview 1.0 as Preview
import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    property var controller: App.instance.controllers.preview;
    property var slot;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.margins: 4;

    height: 220;

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
            label.color: "#FFB80C"
            label.text: "image:"
            label.font.pixelSize: 10;
        }

        Lib.Label
        {
            anchors.verticalCenter: parent.verticalCenter;
            text: slot.name;
            font.pixelSize: 10;
            font.bold: true;
            color: "#fff"
        }
    }

    Lib.IconButton
    {
        anchors.right: parent.right;
        anchors.rightMargin: 4;
        anchors.verticalCenter: header.verticalCenter;

        visible: viewer.image;
        type: types.fa_external_link_square;
        pixelSize: 12;
        onClicked: viewer.showImageInViewer();
    }

    Rectangle
    {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: footerRow.top;

        radius: 2;

        border.color: "#3C424F";
        color: viewer.image ? "#17191F" : "#21252B";

        Preview.ImageViewer
        {
            id: viewer;

            anchors.fill: parent;
            anchors.margins: 2;

            output: root.slot;

            clip: true;
        }

        Lib.Icon
        {
            anchors.centerIn: parent;

            pixelSize: 64;
            type: types.fa_image;
            color: "#283039"
            visible: !viewer.image;
        }
    }

    Row
    {
        id: footerRow;

        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        height: 20;
        spacing: 4;

        property color infoColor: viewer.image ? "#939CAA" : "#21252B";

        Lib.TagLabel
        {
            anchors.verticalCenter: parent.verticalCenter;

            radius: 2;
            color: "#17191F"
            label.color: parent.infoColor;
            label.text: viewer.image ? viewer.image.dimension + "D" : "dim";
            label.font.pixelSize: 10;
        }

        Lib.TagLabel
        {
            anchors.verticalCenter: parent.verticalCenter;

            radius: 2;
            color: "#17191F"
            label.color: parent.infoColor;
            label.text: viewer.image ? viewer.image.pixelString : "pixel";
            label.font.pixelSize: 10;
        }

        Lib.TagLabel
        {
            anchors.verticalCenter: parent.verticalCenter;

            radius: 2;
            color: "#17191F"
            label.color: parent.infoColor;
            label.text: viewer.image ? viewer.image.componentString : "type";
            label.font.pixelSize: 10;
        }
    }
}
