import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    property alias label: label;

    width: label.width + 8;
    height: label.height;
    radius: 4;

    Lib.Label
    {
        id: label;

        anchors.centerIn: parent;
        color: "#fff";
        font.bold: true;
        font.pixelSize: 12;
    }
}
