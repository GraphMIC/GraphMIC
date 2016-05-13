import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.verticalCenter: parent.verticalCenter;

    property var focusView: root.parent;
    property var node: undefined;
    property alias label: label;
    property alias input: input;
    property string initialText;
    property bool resize: false;
    property bool valid: true;

    signal inputFinished(var pInput);

    height: input.height + 6;
    radius: 2;
    clip: true;
    color: isDetail ? "#282C34" : "#131518";
    border.color: isDetail ? input.activeFocus ? "#fff" : ma.containsMouse ? "#939CAA" : "#3C424F" : input.activeFocus ? "#3385ff" : ma.containsMouse ? "#fff" : "#939CAA";

    function clearFocus()
    {
        root.focusView.activate();
    }

    Lib.Label
    {
        id: label;

        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.top: input.top;
        anchors.right: input.left;
        anchors.rightMargin: 4;
        font.pixelSize: isDetail ? 10 : 12;
    }

    Lib.MouseArea
    {
        id: ma;

        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;

        hoverEnabled: true;

        onClicked:
        {
            input.forceActiveFocus();
            root.node.select();
        }
    }

    TextInput
    {
        id: input;

        clip: true;

        property var processed: true;

        anchors.right: parent.right;
        anchors.rightMargin: 6;
        anchors.verticalCenter: parent.verticalCenter;

        color: "#fff"
        font.family: label.font.family;
        font.pixelSize: isDetail ? 10 : 12;
        verticalAlignment: Text.AlignVCenter;
        horizontalAlignment: Text.AlignRight;
        selectionColor: "#4F88FF";
        selectedTextColor: "#fff";
        wrapMode: root.resize ? TextInput.WrapAnywhere : TextInput.NoWrap;

        activeFocusOnPress: true;

        onActiveFocusChanged:
        {
            if (activeFocus)
            {
                root.initialText = input.text;
                processed = false;
            }
            else
            {
                cursorPosition = 0;

                if (!processed)
                {
                    root.inputFinished(input.text);
                }
            }
        }

        Keys.onPressed:
        {
            if (event.key == Qt.Key_Escape)
            {
                processed = true;
                root.inputFinished(root.initialText);
                clearFocus();
            }
            else if (event.key == Qt.Key_Enter || event.key ==  Qt.Key_Return)
            {
                processed = true;
                root.inputFinished(input.text);
                clearFocus();
            }
        }
    }
}
