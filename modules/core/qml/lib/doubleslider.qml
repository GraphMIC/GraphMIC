import QtQuick 2.5

Item
{
    id: root

    property real minimumValue: 0;
    property real maximumValue: 100;
    property real valueLower: minimumValue;
    property real valueUpper: minimumValue;

    width: 200
    height: 11

    onMinimumValueChanged: updatePos();
    onMaximumValueChanged: updatePos();
    onValueLowerChanged: updatePos();
    onValueUpperChanged: updatePos();

    signal valueUpperChangedByHandle;
    signal valueLowerChangedByHandle;

    function updatePos()
    {
        if(slider.width < 1)
        return

        if(maximumValue > minimumValue)
        {
            var posLower = (valueLower-minimumValue)*slider.width/(maximumValue-minimumValue)// - btn1.width
            var posUpper = (valueUpper-minimumValue)*slider.width/(maximumValue-minimumValue) - btn2.width

            btn1.x = posLower
            btn2.x = posUpper
        }
    }

    onWidthChanged:
    {
        updatePos();
    }

    Rectangle
    {
        id: slider
        width: parent.width
        height: parent.height
        anchors.centerIn: parent

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#dd1A1A1A" }
            GradientStop { position: 0.2; color: "#212121" }
        }

        radius: 2

        Rectangle
        {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            height: 2
            color: "#101010"

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#101010" }
                GradientStop { position: 1.0; color: "#ee212121" }
            }
        }


        Rectangle
        {
            height: slider.height - 4
            anchors.left: btn1.left
            anchors.right: btn2.right
            anchors.verticalCenter: parent.verticalCenter

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#69BAFB" }
                GradientStop { position: 1.0; color: "#55A8EB"}
            }
        }

        Rectangle
        {
            id: btn1

            width: 15
            height: 11

            color: "#565656"
            anchors.verticalCenter: parent.verticalCenter

            border.width: 1
            border.color: "#242A31"

            Icon
            {
                anchors.fill: parent
                type: types.fa_ellipsis_h
                pixelSize: 10
                color: "#242A31"
                element.style: Text.Sunken
                element.styleColor: "#ee242A31"
            }

            MouseArea
            {
                id: btn1MouseArea
                anchors.fill: parent
                drag.axis: Drag.XAxis
                drag.target: parent
                drag.minimumX: 0//-btn1.width/2
                drag.maximumX: btn2.x
                drag.threshold: 0

                onPositionChanged:
                {
                    valueLower = Math.max(minimumValue, Math.min(maximumValue, (maximumValue - minimumValue) * (btn1.x)/slider.width + minimumValue))
                    root.valueLowerChangedByHandle();
                }
            }
        }

        Rectangle
        {
            id: btn2

            width: 15
            height: 11
            color: "#565656"
            anchors.verticalCenter: parent.verticalCenter

            border.width: 1
            border.color: "#282828"

            Icon
            {
                anchors.fill: parent
                type: types.fa_ellipsis_h
                pixelSize: 10
                color: "#242A31"
                element.style: Text.Sunken
                element.styleColor: "#ee242A31"
            }

            MouseArea
            {
                id: btn2MouseArea
                anchors.fill: parent
                drag.axis: Drag.XAxis
                drag.target: parent
                drag.minimumX: btn1.x
                drag.maximumX: slider.width - btn2.width

                drag.threshold: 0
                onPositionChanged:
                {
                    valueUpper = Math.max(minimumValue, Math.min(maximumValue, (maximumValue - minimumValue) * (btn2.x + btn2.width)/slider.width + minimumValue))
                    root.valueUpperChangedByHandle();
                }
            }
        }
    }
}
