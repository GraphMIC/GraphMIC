import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.python.node 1.0 as Node

Rectangle
{
    id: root;

    property var designer;

    color: "#21252B"

    Lib.TabHeader
    {
        id: header;

        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.leftMargin: 4;
        anchors.topMargin: 4;
        height: 18;

        Lib.Label
        {
            anchors.verticalCenter: parent.verticalCenter;
            text: "Preview"
            font.pixelSize: 11;
            font.bold: true;
            color: "#fff"
        }
    }

    Rectangle
    {
        anchors.fill: grid;
        color: "#282C34"
        border.color: "#3C424F"
    }

    Lib.Grid
    {
        id: grid;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.top: header.bottom;
        anchors.bottomMargin: 8;
        anchors.leftMargin: 4;
        anchors.rightMargin: 4;

        gridSize: 25
        gridColor: "#29313a"

        clip: true;

        Lib.Grid
        {
            anchors.fill: parent;

            gridSize: 25 * 5;
            gridColor: "#323741"
        }

        Lib.ScrollColumn
        {
            anchors.fill: parent;

            centered: true;
            padding: 40;

            Repeater
            {
                model: designer.node;
                delegate: Node.View
                {
                    node: designer.node;
                }
            }
        }

        AddMenu
        {
            id: addMenu;

            node: designer.node;

            anchors.left: parent.left;
            anchors.bottom: footer.top;
            anchors.leftMargin: 8;
            anchors.bottomMargin: 8;

            width: 120;
        }

        Rectangle
        {
            id: footer;

            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
            height: 28;
            color: "#ee17191F"

            Lib.TextButton
            {
                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.rightMargin: 10;

                label.text: "Create Node"
                label.font.pixelSize: 11;
                color: "#17191F"
                border.color: "#3C424F"

                onClicked: designer.node.create();
            }

            Lib.IconButton
            {
                id: addBtn;

                anchors.left: parent.left;
                anchors.leftMargin: 8;
                anchors.verticalCenter: parent.verticalCenter;

                type: types.fa_plus_circle;
                pixelSize: 16;
                colorNormal: "#fff"
                colorActive: "#00ff00"
                highlight: addMenu.visible;

                onClicked: addMenu.forceActiveFocus();
            }
        }
    }
}
