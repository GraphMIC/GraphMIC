import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Column
{
    property var param;
    property var focusView;
    property bool isDetail: false;

    Item
    {
        anchors.left: parent.left;
        anchors.right: parent.right;

        height: 30;

        Lib.Label
        {
            id: label;

            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.verticalCenter: parent.verticalCenter;
            text: param.name;
            font.pixelSize: root.isDetail ? 10 : 12;
        }
    }

    Item
    {
        anchors.left: parent.left;
        anchors.right: parent.right;

        height: 24;

        Lib.IconButton
        {
            id: btn;

            anchors.left: parent.left;
            anchors.leftMargin: 8;
            anchors.verticalCenter: lbl.verticalCenter;

            type: types.fa_folder_open;

            onClicked: param.showDialog();
        }

        Lib.Label
        {
            id: lbl;

            anchors.left: btn.right;
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.leftMargin: 8;
            text: param.dir;
            font.pixelSize: root.isDetail ? 10 : 12;
        }
    }
}
