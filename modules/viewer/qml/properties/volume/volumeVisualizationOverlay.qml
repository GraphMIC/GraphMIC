import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root

    property alias text: text_field.text
    property alias label: label.text

    color: "#33000000"

    height: 15
    width: 70
    radius: 3

    signal pressed;

    Lib.Label
    {
        id: label
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 4
        font.pixelSize: 9
    }

    TextField
    {
        id: text_field

        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 2
        enabled: root.enabled

        horizontalAlignment: TextInput.AlignRight
        text: "--"
        width: 40

        validator: RegExpValidator
        {
        regExp: /[-+]?[0-9]*\.?[0-9]*/
        }

        Keys.onPressed:
        {
            if (event.key == Qt.Key_Enter || event.key == Qt.Key_Return)
            {
                root.pressed()
            }
        }

        style: TextFieldStyle
        {
            textColor: enabled ? "white" : "#666666"
            font.weight: Font.Normal;
            font.pixelSize: 9;
            background: Rectangle
            {
                color: "transparent"
            }
        }
    }
}
