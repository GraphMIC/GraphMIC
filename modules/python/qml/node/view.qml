import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.python.node 1.0 as Node

Rectangle
{
    id: root;

    property var node;

    width: 220;
    height: container.height;
    color: "#17191F"
    border.color: node.selected ? "#939CAA" : "#3385ff";
    radius: 6;

    Lib.MouseArea
    {
        anchors.fill: parent;
        onClicked: node.clearSelection();
    }

    Column
    {
        id: container;

        anchors.left: parent.left;
        anchors.right: parent.right;

        Item
        {
            id: header;

            anchors.left: parent.left;
            anchors.right: parent.right;
            height: 30;

            Row
            {
                id: hRow;

                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.leftMargin: 6;
                spacing: 4;

                Lib.IconButton
                {
                    anchors.verticalCenter: parent.verticalCenter;

                    type: types.fa_caret_down;
                    enabled: false;
                }

                Lib.TagLabel
                {
                    anchors.verticalCenter: parent.verticalCenter;

                    border.color: "#292D37";
                    color: "#0CB8FF"
                    label.text: "python";
                    label.color: "#000";
                    label.font.pixelSize: 11;
                    radius: 3;
                }
            }

            Lib.Label
            {
                anchors.left: hRow.right;
                anchors.right: btnClose.left;
                anchors.margins: 4;
                anchors.leftMargin: 8;
                anchors.verticalCenter: parent.verticalCenter;

                text: node.name;
                color: "#fff";
                font.bold: true;
            }

            Lib.IconButton
            {
                id: btnClose;

                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.rightMargin: 8;
                clickMargin: 4;
                type: types.fa_times_circle;
            }

            Lib.Edge { align: sides.bottom; color: "#3C424F"; anchors.leftMargin: 1; anchors.rightMargin: 1; }
        }

        Column
        {
            anchors.left: parent.left;
            anchors.right: parent.right;

            Repeater
            {
                model: node.inputs
                delegate: Node.Input
                {
                    param: model.modelData;
                }
            }

            Repeater
            {
                model: node.params;
                delegate: Node.Loader
                {
                    param: model.modelData;
                }
            }

            Repeater
            {
                model: node.outputs;
                delegate: Node.Output
                {
                    param: model.modelData;
                }
            }
        }

        Item
        {
            height: 30;

            anchors.left: parent.left;
            anchors.right: parent.right;

            Row
            {
                id: exRow;

                anchors.top: parent.top;
                anchors.bottom: parent.bottom;
                anchors.right: parent.right;
                anchors.rightMargin: 8;

                visible: node.runnable;

                spacing: 4;

                property var color: "#939CAA"

                Lib.Label
                {
                    anchors.verticalCenter: parent.verticalCenter;
                    color: parent.color;
                    font.bold: true;
                    font.pixelSize: 12;

                    text: "execute";
                }

                Lib.Icon
                {
                    anchors.verticalCenter: parent.verticalCenter;

                    type: types.fa_arrow_circle_o_right;
                    color: parent.color;
                    pixelSize: 16;
                }
            }

            Lib.IconButton
            {
                id: btnHelp;

                anchors.left: parent.left;
                anchors.leftMargin: 8;
                anchors.verticalCenter: parent.verticalCenter;
                type: types.fa_info_circle;
                visible: node.docLink.length > 0;

                onClicked: Qt.openUrlExternally(node.docLink);
            }

            Lib.MouseArea
            {
                id: exMa;

                anchors.fill: exRow;
                // enabled: node.runnable && node.modified;
                hoverEnabled: true;
                // onClicked: node.execute();
            }
        }

        Item
        {
            anchors.left: parent.left;
            anchors.right: parent.right;

            // property bool showFooter: node.runnable || node.useTimer;
            property bool showFooter: true;

            height: showFooter ? 30 : 2;

            Rectangle
            {
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.margins: 1;
                anchors.top: parent.top;
                height: 1;
                visible: parent.showFooter;
                color: "#3C424F";
            }

            Row
            {
                anchors.verticalCenter: parent.verticalCenter;
                anchors.left: parent.left;
                anchors.leftMargin: 8;

                spacing: 4;

                property color timeColor: "#939CAA"
                property bool hasError: false
                property bool wasExecuted: false

                Lib.Icon
                {
                    anchors.verticalCenter: parent.verticalCenter;

                    type: types.fa_clock_o;
                    color: parent.timeColor;
                }

                Lib.Label
                {
                    anchors.verticalCenter: parent.verticalCenter;

                    text: "0ms"
                    color: parent.timeColor;
                    font.bold: true;
                    font.pixelSize: 10;
                }

                Lib.Icon
                {
                    anchors.verticalCenter: parent.verticalCenter;

                    type: parent.hasError ? types.fa_exclamation_circle : types.fa_check_circle;
                    color: parent.hasError ? "#ff0000" : parent.wasExecuted ? "#939CAA" : "#3C424F";
                }
            }

            Lib.Icon
            {
                anchors.right: parent.right;
                anchors.bottom: parent.bottom;
                anchors.rightMargin: -2;
                anchors.bottomMargin: -2;

                type: types.fa_caret_right;
                rotation: 45;
                color: "#939CAA";
                pixelSize: 20;
            }
        }
    }
}
