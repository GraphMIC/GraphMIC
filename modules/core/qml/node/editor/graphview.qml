import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.core.node.editor 1.0 as Editor
import org.graphmic.core.node.object 1.0 as Node
import org.graphmic.core.node.connection 1.0 as Connection

Rectangle
{
    id: root;

    property var controller: App.instance.controllers.nodeEditor;
    property var graph: controller.graph;
    property var connector: controller.connector;
    property alias interactive: flick.interactive;

    color: graph ? "#282C34" : "#21252B";

    Keys.onPressed: event.accepted = controller.onKeyPressed(event.key, event.modifiers, event.text);

    function activate()
    {
        content.forceActiveFocus();
    }

    Lib.MouseArea
    {
        id: ma;

        anchors.fill: parent;
        hoverEnabled: root.visible;
        acceptedButtons: Qt.NoButton;
    }

    onGraphChanged:
    {
        if (graph)
        {
            var pos = graph.position;

            if (pos.x > -1 || pos.y > -1)
            {
                flick.contentX = pos.x;
                flick.contentY = pos.y;
            }
            else
            {
                flick.contentX = flick.contentWidth/2 - root.width/2;
                flick.contentY = flick.contentHeight/2 - root.height/2;
            }
        }
    }

    Lib.Grid
    {
        id: grid;

        anchors.fill: parent;

        visible: root.graph;

        gridSize: controller.gridSize;
        gridColor: "#29313a"
        offsetX: - flick.contentX % gridSize;
        offsetY: - flick.contentY % gridSize;

        Lib.Grid
        {
            anchors.fill: parent;

            gridSize: controller.gridSize * 5;
            gridColor: "#323741"
            offsetX: - flick.contentX % gridSize;
            offsetY: - flick.contentY % gridSize;
        }

        Flickable
        {
            id: flick;

            anchors.fill: parent;
            interactive: ma.containsMouse;
            contentWidth: 10000;
            contentHeight: 10000;
            clip: true;

            property int animXDest: 0;
            property int animYDest: 0;

            PropertyAnimation {id: flickXAnim; target: flick; properties: "contentX"; to: flick.animXDest; duration: 100}
            PropertyAnimation {id: flickYAnim; target: flick; properties: "contentY"; to: flick.animYDest; duration: 100}

            function smoothScrollTo(x,y)
            {
                animXDest = x;
                animYDest = y;

                flickXAnim.start();
                flickYAnim.start();
            }

            Item
            {
                id: content;

                width: flick.contentWidth;
                height: flick.contentHeight;

                Lib.MouseArea
                {
                    anchors.fill: parent;
                    propagateComposedEvents: false;
                    hoverEnabled: false;

                    onPressed:
                    {
                        controller.clearSelection();
                        content.forceActiveFocus();
                    }
                }

                Keys.onPressed:
                {
                    if (!root.graph)
                    {
                        return;
                    }
                    if (event.key == Qt.Key_Space)
                    {
                        controller.setSpawn(ma.mouseX + flick.contentX, ma.mouseY + flick.contentY);

                        var x = ma.mouseX;
                        var y = ma.mouseY;
                        search.show(x,y);
                    }

                    else if (event.key == Qt.Key_Backspace)
                    {
                        controller.deleteSelection();
                    }
                }

                Repeater
                {
                    model: root.graph ? root.graph.connectionList : 0
                    delegate: Connection.View
                    {
                        connection: model.connection;
                    }
                }

                Repeater
                {
                    model: root.graph ? root.graph.nodeList : 0
                    delegate: Node.View
                    {
                        node: model.node;
                        focusView: root;
                    }
                }

                Connection.View
                {
                    connector: root.connector;
                }
            }
        }
    }

    Search
    {
        id: search;
        focusView: content;
    }

    Column
    {
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        anchors.rightMargin: 4;
        spacing: 4;
        visible: App.instance.controllers.debug.debugUI;

        Lib.Label
        {
            anchors.right: parent.right;

            color: "#ff0000";
            text: "active graph: " + root.graph;
        }

        Lib.Label
        {
            anchors.right: parent.right;

            color: "#888";
            text: root.graph ? root.graph.selectionCount + " selections" : "";
        }

        Lib.Label
        {
            id : mouseInfo;

            anchors.right: parent.right;

            color: "#888";
            text: "mouse: x: " + Math.floor(ma.mouseX) + " y: " + Math.floor(ma.mouseY);
        }

        Lib.Label
        {
            anchors.right: parent.right;

            color: "#888";
            text: "scroll: x: " + Math.floor(flick.contentX) + "/" + Math.floor(flick.contentWidth) +  " y: " + Math.floor(flick.contentY) + "/" + Math.floor(flick.contentHeight);
        }
    }

    function moveToNode(node)
    {
        var x = node.position.x - root.width / 2 + node.size.x / 2;
        var y = node.position.y - root.height / 2 + node.size.y / 2;

        flick.smoothScrollTo(x,y);
    }

    Lib.Edge {
        color: "#3C424F"
        align: sides.left;
    }

    Connections
    {
        target: root.controller

        onSaveGraphState: root.graph.setPosition(flick.contentX, flick.contentY);
        onMoveToNode: root.moveToNode(node);
    }

    Component.onCompleted:
    {
        controller.setSpawn(flick.contentWidth/2 + 20,
            flick.contentHeight/2 + 20);
    }
}
