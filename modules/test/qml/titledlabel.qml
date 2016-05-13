import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Row
{
    property alias title: title;
    property alias tag: tag;

    anchors.verticalCenter: parent.verticalCenter;
    spacing: 4;

    Lib.Label
    {
        id: title;

        anchors.verticalCenter: parent.verticalCenter;
    }

    Lib.TagLabel
    {
        id: tag;

        anchors.verticalCenter: parent.verticalCenter;

        color: "#222"
        radius: 2;
    }
}
