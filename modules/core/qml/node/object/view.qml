import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.core.node.param 1.0 as Param
import org.graphmic.core.node.slot 1.0 as Slot

Rectangle
{
    id: root;

    property var node: undefined;
    property var editor: App.instance.controllers.nodeEditor
    property var focusView: root.parent;

    width: anchor.x;
    height: container.height;
    color: "#17191F"
    border.color: node.selected ? "#fff" : "#939CAA";
    radius: 6;
    z: node.layer;

    Item
    {
        id: anchor;

        x: 200;
        width: 1;
        height: 1;
    }

    Lib.MouseArea
    {
        anchors.fill: parent;

        drag.target: parent;
        drag.smoothed: false;

        property bool dragging: drag.active;

        onDraggingChanged:
        {
            var gridSize = controller.gridSize;

            if (dragging)
            {
                node.raise();
                node.select();
            } else if (editor.snap) {
                root.x = Math.round(root.x / gridSize) * gridSize;
                root.y = Math.round(root.y / gridSize) * gridSize;
            }
        }
        onClicked:
        {
            root.focusView.activate();

            node.raise();
            node.select();
        }
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

                    type: types.fa_caret_right;
                    rotation: node.expanded ? 90 : 0;

                    onClicked: node.toggleExpansion();
                }

                Lib.TagLabel
                {
                    anchors.verticalCenter: parent.verticalCenter;

                    border.color: "#292D37";
                    color: "#0CB8FF"
                    label.text: node.lib
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
                enabled: node.deletable;
                visible: !node.running;
                onClicked: node.remove();
            }

            Lib.IconButton
            {
                anchors.centerIn: btnClose;
                visible: node.running;
                type: types.fa_refresh;
                color: "#ff5511"

                RotationAnimator on rotation {
                    duration: 800
                    loops: Animation.Infinite
                    from: 0
                    to: 360
                    running: node.running
                }
            }

            Lib.Edge { align: sides.bottom; color: "#3C424F"; anchors.leftMargin: 1; anchors.rightMargin: 1; }
        }

        Column
        {
            anchors.left: parent.left;
            anchors.right: parent.right;

            Repeater
            {
                model: node.inputList;
                delegate: Slot.Input
                {
                    id: md;

                    slot: model.slot;

                    Binding
                    {
                        target: slot;
                        property: "x";
                        value: root.x;
                    }

                    Binding
                    {
                        target: slot;
                        property: "y";
                        value: root.y + header.height + y + height/2;
                    }
                }
            }

            Repeater
            {
                model: node.expanded ? node.groupList : 0;
                delegate: Param.Group
                {
                    group: model.group;
                    focusView: root.focusView;
                }
            }

            Repeater
            {
                model: node.outputList;
                delegate: Slot.Output
                {
                    slot: model.slot;

                    Binding
                    {
                        target: slot;
                        property: "x";
                        value: root.x + root.width;
                    }

                    Binding
                    {
                        target: slot;
                        property: "y";
                        value: root.y + header.height + y + height/2;
                    }
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

                spacing: 4;
                visible: node.runnable;

                property var color: node.forceExecution || node.modified ? exMa.containsMouse ? "#fff" : "#939CAA" : "#3C424F";

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
                enabled: node.runnable && (node.forceExecution || node.modified);
                hoverEnabled: true;
                onClicked: node.execute();
            }
        }

        Item
        {
            anchors.left: parent.left;
            anchors.right: parent.right;

            property bool showFooter: node.runnable || node.useTimer;

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

                property color timeColor: node.time < 1 ? "#3C424F" : node.time < 200 ? "#939CAA" : node.time < 1000 ? "#FFE5B4" : "#ff9933";
                property bool hasError: node.errorCount > 0;
                property bool wasExecuted: node.time > 0;

                Lib.Icon
                {
                    anchors.verticalCenter: parent.verticalCenter;

                    visible: node.useTimer;

                    type: types.fa_clock_o;
                    color: parent.timeColor;
                }

                Lib.Label
                {
                    anchors.verticalCenter: parent.verticalCenter;

                    visible: node.useTimer;

                    text: node.time < 1000 ? node.time + " ms" : Math.round(node.time * 10) / 10000 + " sec";
                    color: parent.timeColor;
                    font.bold: true;
                    font.pixelSize: 10;
                }

                Lib.Icon
                {
                    anchors.verticalCenter: parent.verticalCenter;

                    visible: node.runnable;
                    type: parent.hasError ? types.fa_exclamation_circle : types.fa_check_circle;
                    color: parent.hasError ? "#ff0000" : parent.wasExecuted ? "#939CAA" : "#3C424F";
                }

                Lib.Label
                {
                    anchors.verticalCenter: parent.verticalCenter;

                    color: "#fff"
                    visible: parent.hasError && node.runnable;
                    text: node.errorCount;
                    font.bold: true;
                    font.pixelSize: 10;
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
                color: resizer.drag.active | resizer.containsMouse ? "#fff" : "#939CAA";
                pixelSize: 20;

                Lib.MouseArea
                {
                    id: resizer;

                    anchors.fill: parent;
                    hoverEnabled: true;
                    drag.target: anchor;
                    drag.axis: Drag.XAxis;
                    drag.minimumX: 200;
                    drag.maximumX: 800;
                }
            }
        }
    }

    Component.onCompleted:
    {
        var pos = node.position;

        if (pos.x > -1 || pos.y > -1)
        {
            root.x = pos.x;
            root.y = pos.y;
        } else {
            root.x = 0;
            root.y = 0;
        }

        if (controller.snap) {
            var gridSize = controller.gridSize;
            root.x = Math.round(root.x / gridSize) * gridSize;
            root.y = Math.round(root.y / gridSize) * gridSize;
        }

        anchor.x = node.size.x;
    }

    function updateGeometry()
    {
        node.setGeometry(root.x, root.y, root.width, root.height);
    }

    Connections
    {
        target: editor

        onSaveGraphState: root.updateGeometry();
    }

    Connections
    {
        target: node

        onUpdateGeometry: root.updateGeometry();
    }
}
