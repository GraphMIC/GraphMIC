import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.core.node.param 1.0 as Param

Column
{
    id: root;

    anchors.left: parent ? parent.left : undefined;
    anchors.right: parent ? parent.right : undefined;

    property var group;
    property var focusView: parent;
    property bool isDetail: false;

    Row
    {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.leftMargin: 8;
        anchors.rightMargin: 8;

        height: label.height + 8;
        visible: group.size > 0 && label.text.length > 0;
        spacing: 4;
        clip: true;

        Lib.IconButton
        {
            anchors.verticalCenter: parent.verticalCenter;

            type: types.fa_caret_right;
            rotation: group.expanded ? 90 : 0;
            visible: !root.isDetail;
            enabled: visible;

            onClicked: group.toggleExpansion();
        }

        Lib.Label
        {
            id: label;

            text: group.name;
            anchors.verticalCenter: parent.verticalCenter;
            color: root.isDetail ? "#939CAA" : "#fff";
            font.bold: true;
            font.pixelSize: 10;
        }
    }

    Column
    {
        id: col;

        anchors.left: parent.left;
        anchors.right: parent.right;
        visible: root.isDetail ? true : group.expanded;

        Repeater
        {
            model: group.paramList
            delegate: Param.Loader
            {
                param: model.param;
                focusView: root.focusView;
                isDetail: root.isDetail;
            }
        }
    }
}
