import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.leftMargin: 4;
    anchors.rightMargin: 4;

    property alias label: label;
    property alias input: input;

    signal inputFinished(var newText);

    height: 24

    Lib.Label
    {
        id: label;

        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        width: 80;
        color: "#fff"
    }

    Lib.TextInput
    {
        id: input;

        anchors.left: label.right;
        anchors.right: parent.right;
        anchors.leftMargin: 4;
        anchors.verticalCenter: parent.verticalCenter;

        borderDefault: "#3C424F"
        color: "#282C34"
        clip: true;

        showBorder: true;
        editOnClick: true;

        onInputFinished:
        {
            root.inputFinished(newText);
            root.forceActiveFocus();
        }
    }
}
