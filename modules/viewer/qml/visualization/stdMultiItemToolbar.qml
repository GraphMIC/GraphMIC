import QtQuick 2.4
import org.graphmic.core.lib 1.0 as Lib

Column
{
    id: root
    property var multiItem;

    Rectangle
    {
        height: 35
        anchors.left: parent.left
        anchors.right: parent.right

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#323741" }
            GradientStop { position: 0.1; color: "#282C34" }
        }

        Rectangle
        {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color: "#4C4C4C"
        }

        Row
        {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            spacing: 15

            Lib.Label
            {
                anchors.verticalCenter: parent.verticalCenter;
                text: "Crosshair";
                color: "#939CAA"
            }

            Lib.IconButton
            {
                id: planeToggle
                anchors.verticalCenter: parent.verticalCenter;
                type: highlight ? types.fa_toggle_on: types.fa_toggle_off
                enabled: true
                pixelSize: 18
                colorActive: "#939CAA"
                highlight: true

                onClicked:
                {
                  highlight = !highlight
                  multiItem.togglePlanes();
                }
            }

            Lib.Label
            {
                anchors.verticalCenter: parent.verticalCenter;
                text: "Crosshair Mode";
                color: "#939CAA"
            }

            Lib.DropDown
            {
                anchors.verticalCenter: parent.verticalCenter;
                width: 150
                enabled: planeToggle.highlight

                model: [
                "No Crosshair Rotation",
                "Crosshair Rotation",
                "Coupled Crosshair Rotation",
                "Swivel"
                ]

                onCurrentIndexChanged:
                {
                    multiItem.mouseMode = currentIndex
                }
            }

            Lib.TextButton
            {
                label.text: "Global Reinit"

                onClicked: multiItem.globalReinit()
            }
        }
    }
}
