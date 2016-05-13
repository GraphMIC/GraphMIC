import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.viewer.properties.volume 1.0 as Volume
import GM 1.0 as GM

ColumnLayout
{
    spacing: 0

    GM.TransferFunctionItem
    {
        id: root
    }

    Rectangle
    {
        height: 150
        anchors.left: parent.left
        anchors.right: parent.right
        border.color: "#1E1E1E"
        border.width: 1;
        radius: 2;
        color: "transparent"

        GM.PiecewiseFunctionCanvas
        {
            id: opacityItem
            anchors.fill: parent
            anchors.margins: 1

            enabled: root.enabled

            Volume.Overlay
            {
                id: opacityField
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.topMargin: 2
                label: "Opacity"
                enabled: root.enabled

                onPressed:
                {
                    opacityItem.opacity = text
                }
            }

            Volume.Overlay
            {
                id: grayField
                anchors.top: opacityField.bottom
                anchors.right: parent.right
                anchors.topMargin: 2
                label: "Value"
                enabled: root.enabled

                onPressed:
                {
                    opacityItem.greyValue = text
                }
            }

            Volume.Overlay
            {
                id: colorField
                anchors.top: grayField.bottom
                anchors.right: parent.right
                anchors.topMargin: 2
                label: "Color"
                enabled: root.enabled

                onPressed:
                {
                    colorItem.greyValue = text
                }
            }
        }
    }

    GM.ColorTransferFunctionCanvas
    {
        Layout.topMargin: -5

        id: colorItem
        anchors.left: parent.left
        anchors.right: parent.right
        height: 16
        enabled: root.enabled
    }

    Lib.DoubleSlider
    {
        id: slider

        Layout.topMargin: 5

        anchors.left: parent.left
        anchors.right: parent.right

        minimumValue: root.min;
        maximumValue: root.max;

        onValueLowerChangedByHandle:
        {
            root.currentMin = valueLower;
        }

        onValueUpperChangedByHandle:
        {
            root.currentMax = valueUpper;
        }
    }

    Connections
    {
        target: colorItem;

        onSync:
        {
            colorField.text = colorItem.greyValue.toFixed(2);
        }
    }


    Connections
    {
        target: opacityItem;

        onSync:
        {
            grayField.text = opacityItem.greyValue.toFixed(2);
            opacityField.text = opacityItem.opacity.toFixed(2);
        }
    }

    Connections
    {
        target: root

        onSync:
        {
            slider.valueUpper = root.currentMax
            slider.valueLower = root.currentMin
        }
    }

    Component.onCompleted:
    {
        root.opacityItem = opacityItem;
        root.colorItem = colorItem;
    }
}
