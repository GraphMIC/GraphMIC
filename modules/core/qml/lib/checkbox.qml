import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root;

    property bool checked: false;
    signal clicked();

    width: 14;
    height: 14;
    radius: 2;

    color: "#282C34";
    border.color: "#3C424F"

    Lib.Icon
    {
        anchors.centerIn: parent
        visible: root.checked;
        type: types.fa_check;
        color: "#fff";
        pixelSize: 10;
    }

    Lib.MouseArea
    {
        anchors.fill: parent;
        onClicked:
        {
            root.clicked();
            mouse.accepted = false;
        }
    }
}
