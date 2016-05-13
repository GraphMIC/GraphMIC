import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.preview 1.0 as Preview
import org.graphmic.core.lib 1.0 as Lib

Row
{
    id: root;

    property var controller: App.instance.controllers.preview;
    property var count: controller.stackSize;
    property var index: controller.stackIndex;

    spacing: 4;

    Lib.IconButton
    {
        anchors.verticalCenter: stackLabel.verticalCenter;

        colorNormal: "#939CAA";
        colorDisabled: "#3C424F";
        type: types.fa_chevron_circle_left;
        pixelSize: 12;
        onClicked: controller.decrementIndex();
        enabled: root.count > 1;
    }

    Lib.TagLabel
    {
        id: stackLabel;

        color: ma.containsMouse || ma.pressed ? "#fff" : "#939CAA";
        width: 40;
        label.text: root.count > 1 ? (root.index + 1) + "/" + root.count : root.count;
        label.color: "#000"
        label.font.pixelSize: 10;

        Lib.MouseArea
        {
            id: ma;

            anchors.fill: parent;
        }
    }

    Lib.IconButton
    {
        anchors.verticalCenter: stackLabel.verticalCenter;

        colorNormal: "#939CAA";
        colorDisabled: "#3C424F";
        type: types.fa_chevron_circle_right;
        pixelSize: 12;
        onClicked: controller.incrementIndex();
        enabled: root.count > 1;
    }
}
