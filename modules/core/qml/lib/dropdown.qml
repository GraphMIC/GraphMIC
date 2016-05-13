import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import org.graphmic.core.lib 1.0 as Lib

ComboBox
{
    id: root;

    height: 20;
    width: 100;

    property color backgroundColor: "#31363E";
    property color borderColor: "#1E1E1E";
    property color textActive: "#fff";
    property color textNormal: "#939CAA"
    property bool interactive: false;

    signal renameOption(string newName);
    signal addOption();
    signal removeOption();

    anchors.rightMargin: interactive ? row.width + 4 : 0;

    style: ComboBoxStyle
    {
        background: Rectangle
        {
            id: compBackground;

            border.color: root.borderColor;
            border.width: 1;
            radius: 2;

            color: root.backgroundColor;
            width: parent.width;
            height: parent.height;

            Lib.Icon
            {
                anchors.verticalCenter: parent.verticalCenter;
                anchors.verticalCenterOffset: -2;
                anchors.right: parent.right;
                anchors.rightMargin: 6;

                type: types.fa_sort_down;
                color: root.enabled ? ma.containsMouse  ? "#FFF" : "#939CAA" : "#666";
                pixelSize: 10;
            }
        }

        label: Lib.Label
        {
            id: compLabel;

            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.rightMargin: 10;
            anchors.verticalCenter: parent.verticalCenter;

            text: control.currentText
            color: root.enabled ? ma.containsMouse  ? "#FFF" : "#939CAA" : "#666";
        }
    }

    Lib.TextInput
    {
        id: input;

        anchors.fill: parent;
        anchors.margins: 2;
        anchors.rightMargin: 20;
        visible: enabled;
        enabled: root.interactive;

        showBorder: false;
        color: root.backgroundColor;

        editOnClick: true;
        text: root.currentText;

        clip: true;

        onInputFinished:
        {
            root.renameOption(newText)
            root.parent.forceActiveFocus();
        }

        Rectangle
        {
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;

            width: 1;
            color: root.borderColor;
        }
    }

    Lib.MouseArea
    {
        id: ma;

        anchors.fill: parent;

        acceptedButtons: root.interactive ? Qt.AllButtons : Qt.NoButton;

        onPressed:
        {
            if (mouse.x < root.width - 20) {
                input.edit();
                mouse.accepted = true;
            }
            mouse.accepted = false;
        }
    }

    Row
    {
        id: row;

        enabled: root.interactive;
        visible: enabled;

        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.right;
        anchors.leftMargin: 4;

        spacing: 4;

        Lib.IconButton
        {
            anchors.verticalCenter: parent.verticalCenter;
            type: types.fa_plus_circle;
            colorActive: "#00ff00"
            enabled: root.count < 20;

            onClicked: {
                root.addOption();
                input.edit();
            }
        }

        Lib.IconButton
        {
            anchors.verticalCenter: parent.verticalCenter;
            type: types.fa_times_circle;
            colorActive: "#ff0000";
            enabled: root.count > 1;

            onClicked: root.removeOption();
        }
    }
}
