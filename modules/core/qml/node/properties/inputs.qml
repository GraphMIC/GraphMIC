import QtQuick 2.5
import QtQuick.Controls 1.4

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.core.node.slot 1.0 as Slot

Column
{
    id: root;

    property var focusView: undefined;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.margins: 6;
    spacing: 4;

    Repeater
    {
        model: node ? node.inputList : 0

        delegate: Item
        {
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.margins: 6;
            height: 24;

            property var slot: model.slot;
            property int isRight: slot.direction;

            Row
            {
                anchors.verticalCenter: parent.verticalCenter;
                anchors.left: parent.left;

                spacing: 6;

                LayoutMirroring.enabled: parent.isRight;

                Rectangle
                {
                    id: indicator;

                    anchors.verticalCenter: parent.verticalCenter;

                    width: 8;
                    height: width;
                    radius: width/2;
                    color: slot.hasData ? "#fff" : "#242A31"
                    border.color: slot.hasData ? "#000" : "#939CAA"
                }

                Lib.Label
                {
                    anchors.verticalCenter: parent.verticalCenter;

                    color: slot.hasData ? "#fff" : "#939CAA"
                    font.pixelSize: 10;
                    font.bold: true;
                    text: slot.name;
                }
            }
        }
    }
}
