import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    default property alias content: column.children;

    property bool centered: false;
    property int padding: 0;
    property alias handle: handle;

    clip: true;

    Flickable
    {
        id: flick;

        anchors.fill: parent;

        contentWidth: root.width;
        contentHeight: container.height;

        boundsBehavior: Flickable.StopAtBounds;
        flickableDirection: Flickable.VerticalFlick;
        flickDeceleration: 5000;

        rebound: Transition
        {
            NumberAnimation
            {
                properties: "y"
                duration: 0
            }
        }

        Item
        {
            id: container;

            width: root.width;
            height: Math.max(root.height, column.height + root.padding);

            Column
            {
                id: column;

                anchors.left: root.centered ? undefined : parent.left;
                anchors.right: root.centered ? undefined : parent.right;
                anchors.centerIn: root.centered ? parent : undefined;
                anchors.top: root.centered ? undefined : parent.top;
            }
        }
    }

    Rectangle
    {
        id: handle;

        property bool dragging: ma.drag.active;

        anchors.right: parent.right;
        anchors.rightMargin: 2;

        visible: flick.contentHeight > root.height;
        enabled: visible;

        y: flick.visibleArea.yPosition * root.height;
        width: 8
        height: flick.visibleArea.heightRatio * root.height
        radius: width/2;

        color: "#131518"
        border.color: "#3C424F"

        Lib.MouseArea
        {
            id: ma;

            anchors.fill: parent;
            drag.target: parent;
            drag.axis: Drag.YAxis;
            drag.minimumY: 0;
            drag.maximumY: root.height - handle.height;
        }

        onDraggingChanged:
        {
            if (dragging)
            {
                handle.y = handle.y;
                flick.contentY = Qt.binding(function() {
                    return handle.y/(root.height - handle.height) * (flick.contentHeight - root.height);
                });
            }
            else {
                flick.contentY = flick.contentY;
                handle.y = Qt.binding(function() {
                    return flick.visibleArea.yPosition * root.height;
                });
            }
        }
    }
}
