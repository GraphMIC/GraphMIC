import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    property alias view1: container1.children;
    property alias view2: container2.children;

    property string label1: "";
    property string label2: "";
    property bool showHandles: resizeable;
    property bool resizeable: true;
    property var orientation: Qt.Horizontal;
    property int minBottom: 100;
    property int minRight: 100;
    property int minLeft: 100;
    property int minTop: 100;
    property int handleRadius: 4;
    property int handleWidth: 30;
    property int handleHeight: 100;
    property color iconColor: ma.containsMouse ? "#fff" : "#aaa"
    property color handleColor: "#131518";
    property color handleBorder: ma.containsMouse || ma.pressed ? Qt.lighter("#3C424F") : "#3C424F";

    clip: true;

    function setSplitLocation(val) {
        console.log("set split location to: " + val);
        if (orientation == Qt.Horizontal) {
            anchor.x = val;
        } else {
            anchor.y = val;
        }

        lockAnchor();
    }

    function collapseLeft() {
        anchor.anchors.right        = undefined;
        anchor.anchors.left         = root.left;
        anchor.anchors.rightMargin  = 0;

        anchor.anchors.leftMargin = 0;
        container1.minimized = true;
        container2.minimized = false;
    }

    function collapseRight() {
        anchor.anchors.left         = undefined;
        anchor.anchors.right        = root.right;
        anchor.anchors.leftMargin   = 0;

        anchor.anchors.rightMargin = 0;
        container2.minimized = true;
        container1.minimized = false;
    }

    function expandLeft(margin) {
        anchor.anchors.right        = undefined;
        anchor.anchors.left         = root.left;
        anchor.anchors.rightMargin  = 0;

        anchor.anchors.leftMargin = Qt.binding (function(){ return Math.min (margin, root.width); });
        container1.minimized = false;
        container2.minimized = false;
    }

    function expandRight(margin) {
        anchor.anchors.left         = undefined;
        anchor.anchors.right        = root.right;
        anchor.anchors.leftMargin   = 0;

        anchor.anchors.rightMargin = Qt.binding (function() { return Math.min (margin, root.width); });
        container2.minimized = false;
        container1.minimized = false;
    }

    function collapseTop() {
        anchor.anchors.bottom       = undefined;
        anchor.anchors.top          = root.top;
        anchor.anchors.bottomMargin = 0;

        anchor.anchors.topMargin = 0;
        container1.minimized = true;
        container2.minimized = false;
    }

    function expandTop(margin) {
        anchor.anchors.bottom       = undefined;
        anchor.anchors.top          = root.top;
        anchor.anchors.bottomMargin = 0;

        anchor.anchors.topMargin = Qt.binding (function() { return Math.min (margin, root.height); });
        container1.minimized = false;
        container2.minimized = false;
    }

    function collapseBottom() {
        anchor.anchors.top          = undefined;
        anchor.anchors.bottom       = root.bottom;
        anchor.anchors.topMargin    = 0;

        anchor.anchors.bottomMargin = 0;
        container2.minimized = true;
        container1.minimized = false;
    }

    function expandBottom(margin) {
        anchor.anchors.top          = undefined;
        anchor.anchors.bottom       = root.bottom;
        anchor.anchors.topMargin    = 0;

        anchor.anchors.bottomMargin = Qt.binding (function() { return Math.min (margin, root.height); });
        container2.minimized = false;
        container1.minimized = false;
    }

    function lockAnchor()
    {
        if (orientation == Qt.Horizontal) {
            if (anchor.x > width / 2) {
                var margin = root.width - anchor.x;

                if (margin < minRight) {
                    collapseRight();
                } else {
                    expandRight(margin);
                }
            } else {
                var margin = anchor.x;

                if (margin < minLeft) {
                    collapseLeft();
                } else {
                    expandLeft(margin);
                }
            }
        } else {
            if (anchor.y > height / 2) {
                var margin = root.height - anchor.y;

                if (margin < minBottom) {
                    collapseBottom();
                } else {
                    expandBottom(margin);
                }
            } else {
                var margin = anchor.y;

                if (margin < minTop) {
                    collapseTop();
                } else {
                    expandTop(margin);
                }
            }
        }
    }

    function unlockAnchor() {
        if (orientation == Qt.Horizontal) {
            anchor.anchors.left     = undefined;
            anchor.anchors.right    = undefined;
        } else {
            anchor.anchors.top      = undefined;
            anchor.anchors.bottom   = undefined;
        }
    }

    Item
    {
        id: container1;

        property real sizeFac: root.orientation == Qt.Horizontal ? (1 - Math.min(1, width / 16)) : (1 - Math.min(1, height / 16));
        property bool minimized: false;

        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: root.orientation == Qt.Horizontal ? parent.bottom : anchor.top;
        anchors.right: root.orientation == Qt.Horizontal ? anchor.left : parent.right;
    }

    Item
    {
        id: container2;

        property real sizeFac: root.orientation == Qt.Horizontal ? (1 - Math.min(1, width / 16)) : (1 - Math.min(1, height / 16));
        property bool minimized: false;

        anchors.top: root.orientation == Qt.Horizontal ? parent.top : anchor.bottom;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        anchors.left: root.orientation == Qt.Horizontal ? anchor.right : parent.left;
    }

    Rectangle
    {
        id: anchor;

        anchors.top: root.orientation == Qt.Horizontal ? parent.top : undefined;
        anchors.bottom: root.orientation == Qt.Horizontal ? parent.bottom : undefined;
        anchors.left: root.orientation == Qt.Vertical ? parent.left : undefined;
        anchors.right: root.orientation == Qt.Vertical ? parent.right : undefined;

        width: 1;
        height: 1;

        color: root.handleBorder;
    }

    Rectangle
    {
        id: handle1;

        visible: root.showHandles;
        enabled: visible;

        anchors.right: root.orientation == Qt.Horizontal ? parent.right : undefined;
        anchors.bottom: root.orientation == Qt.Vertical ? parent.bottom : undefined;
        anchors.verticalCenter: root.orientation == Qt.Horizontal ? parent.verticalCenter : undefined;
        anchors.horizontalCenter: root.orientation == Qt.Vertical ? parent.horizontalCenter : undefined;
        anchors.rightMargin: root.orientation == Qt.Horizontal ? container2.sizeFac * width / 2 - width : 0;
        anchors.bottomMargin: root.orientation == Qt.Vertical ? container2.sizeFac * height / 2 - height : 0;

        width: root.orientation == Qt.Horizontal ? root.handleWidth : root.handleHeight;
        height: root.orientation == Qt.Horizontal ? root.handleHeight : root.handleWidth;
        radius: root.handleRadius;

        color: root.handleColor;
        border.color: root.handleBorder;

        Lib.Icon
        {
            id: ic1;

            anchors.verticalCenter: root.orientation == Qt.Horizontal ? parent.verticalCenter : undefined;
            anchors.horizontalCenter: root.orientation == Qt.Vertical ? parent.horizontalCenter : undefined;
            anchors.left: root.orientation == Qt.Horizontal ? parent.left : undefined;
            anchors.top: root.orientation == Qt.Vertical ? parent.top : undefined;
            anchors.margins: root.orientation == Qt.Horizontal ? width / 6 : height / 6;

            visible: root.label2.length < 1;
            type: root.orientation == Qt.Horizontal ? types.fa_caret_left : types.fa_caret_up;
            color: root.iconColor;
        }

        Lib.Label
        {
            id: lb1;

            anchors.centerIn: ic1;
            rotation: root.orientation == Qt.Horizontal ? - 90 : 0;
            text: root.label2;
            color: root.iconColor;
            font.bold: true;
        }

        Lib.MouseArea
        {
            anchors.fill: parent;
            enabled: container2.minimized;

            onClicked: {
                unlockAnchor();

                if (root.orientation == Qt.Horizontal) {
                    setSplitLocation (root.width - root.minRight);
                } else {
                    setSplitLocation (root.height - root.minBottom);
                }
            }
        }
    }

    Rectangle
    {
        id: handle2;

        visible: root.showHandles;
        enabled: visible;

        anchors.left: root.orientation == Qt.Horizontal ? parent.left : undefined;
        anchors.top: root.orientation == Qt.Vertical ? parent.top : undefined;
        anchors.verticalCenter: root.orientation == Qt.Horizontal ? parent.verticalCenter : undefined;
        anchors.horizontalCenter: root.orientation == Qt.Vertical ? parent.horizontalCenter : undefined;
        anchors.leftMargin: root.orientation == Qt.Horizontal ? container1.sizeFac * width / 2 - width : 0;
        anchors.topMargin: root.orientation == Qt.Vertical ? container1.sizeFac * height / 2 - height : 0;

        width: root.orientation == Qt.Horizontal ? root.handleWidth : root.handleHeight;
        height: root.orientation == Qt.Horizontal ? root.handleHeight : root.handleWidth;
        radius: root.handleRadius;

        color: root.handleColor;
        border.color: root.handleBorder;

        Lib.Icon
        {
            id: ic2;

            anchors.verticalCenter: root.orientation == Qt.Horizontal ? parent.verticalCenter : undefined;
            anchors.horizontalCenter: root.orientation == Qt.Vertical ? parent.horizontalCenter : undefined;
            anchors.right: root.orientation == Qt.Horizontal ? parent.right : undefined;
            anchors.bottom: root.orientation == Qt.Vertical ? parent.bottom : undefined;
            anchors.margins: root.orientation == Qt.Horizontal ? width / 6 : height / 6;

            visible: root.label1.length < 1;
            type: root.orientation == Qt.Horizontal ? types.fa_caret_right : types.fa_caret_down;
            color: root.iconColor;
        }

        Lib.Label
        {
            id: lb2;

            anchors.centerIn: ic2;
            rotation: root.orientation == Qt.Horizontal ? - 90 : 0;
            text: root.label1;
            color: root.iconColor;
            font.bold: true;
        }

        Lib.MouseArea
        {
            anchors.fill: parent;
            enabled: container1.minimized;

            onClicked: {
                unlockAnchor();

                if (root.orientation == Qt.Horizontal) {
                    setSplitLocation (root.minLeft);
                } else {
                    setSplitLocation (root.minTop);
                }
            }
        }
    }

    Lib.MouseArea
    {
        id: ma;

        anchors.fill: anchor;

        enabled: root.resizeable;

        anchors.leftMargin: root.orientation == Qt.Horizontal ? container2.minimized ? - root.handleWidth / 2 : - 6 : 0;
        anchors.rightMargin: root.orientation == Qt.Horizontal ? container1.minimized ? - root.handleWidth / 2 : - 6 : 0;
        anchors.topMargin: root.orientation == Qt.Vertical ? container2.minimized ? - root.handleWidth / 2 : - 6 : 0;
        anchors.bottomMargin: root.orientation == Qt.Vertical ? container1.minimized ? - root.handleWidth / 2 : - 6 : 0;

        hoverEnabled: true;

        drag.target: anchor;
        drag.minimumX: 0;
        drag.maximumX: root.width;
        drag.minimumY: 0;
        drag.maximumY: root.height;
        drag.axis: root.orientation == Qt.Horizontal ? Drag.XAxis : Drag.YAxis;

        onPressed: root.unlockAnchor();
        onReleased: root.lockAnchor();
    }
}
