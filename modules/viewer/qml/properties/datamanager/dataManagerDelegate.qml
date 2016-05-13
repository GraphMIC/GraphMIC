import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib
import GM 1.0 as GM

Column
{
    id: root;

    property var listController;
    property alias listLabel: label;
    property bool shadow: false;
    anchors.left: parent.left
    anchors.right: parent.right
    property var dataManager: Module.controllers["Manager"];

    Rectangle
    {
        anchors.left: parent.left
        anchors.right: parent.right
        height: 1
        color: "#1E1E1E"
    }

    Rectangle
    {
        id: maskingLabel
        anchors.left: parent.left
        anchors.right: parent.right
        height: 22
        color: "#21252B"

        Lib.Label
        {
            id: label;
            anchors.left: parent.left;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.leftMargin: 16

            text: "";
            //style: Text.Sunken
            //font.capitalization: Font.AllUppercase
            //font.weight: Font.DemiBold
            color: "#7D8285"
        }

        Lib.IconButton
        {
            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: label.right
            anchors.leftMargin: 5
            type: types.fa_plus_circle
            color: "#7D8285"
            element.style: Text.Sunken
            pixelSize: 14

            onClicked: listController.addNode()
        }

        /*
        layer.enabled: shadow;
        layer.effect: InnerShadow
        {
            visible: true
            radius: 2
            samples: 16
            horizontalOffset: 0
            verticalOffset: 2
            color: "#21252B"
            source: maskingLabel
        }*/

        Rectangle
        {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 4
            color: "#272C33"
        }

        Rectangle
        {
            height: 6
            width: 6

            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            color: "#272C33"
            transform: Rotation { origin.x: 3; origin.y: 3; angle: 45}
        }
    }

    Column
    {
        anchors.left: parent.left
        anchors.right: parent.right

        Repeater
        {
            model: listController.model

            Rectangle
            {
                id: listItem
                anchors.left: parent ? parent.left : undefined
                anchors.right: parent ? parent.right : undefined
                color: "#21252B"
                height: 22

                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                        listController.index  = index
                    }
                }

                RowLayout
                {
                    anchors.fill: parent
                    Rectangle
                    {
                        Layout.alignment : Qt.AlignLeft
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        width: 4
                        color: model.decoration ? "#aa5896BB" : "#272C33";
                    }

                    Lib.IconButton
                    {
                        id: btn;

                        Layout.leftMargin: 5
                        anchors.verticalCenter: parent.verticalCenter;
                        type: highlight ? types.fa_eye : types.fa_eye_slash;
                        colorActive: "#939CAA"
                        color: "#939CAA"
                        highlight: true
                        pixelSize: 12
                        onClicked:
                        {
                            highlight = !highlight;
                            listController.index  = index
                            listController.toggleVisibility(checked)
                        }
                    }

                    Item
                    {
                        Layout.fillWidth: true
                        Layout.leftMargin: 5

                        Lib.TextInput
                        {
                            anchors.verticalCenter: parent.verticalCenter
                            text: model.display
                            editOnClick: false
                            layout: layouts.left;
                            textSize: 11

                            onInputConfirmed: listController.changeNodeName(index, text);
                            onInputFinished: parent.forceActiveFocus()
                        }
                    }
                }
            }
        }
    }
}
