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
    property alias dropdown: dropdown;

    signal indexChanged(int index);
    signal renameOption(string newName);
    signal addOption();
    signal removeOption();

    height: 24

    Lib.Label
    {
        id: label;

        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        width: 80;
        color: enabled ? "#fff" : "#939CAA"
    }

    Lib.DropDown
    {
        id: dropdown;

        anchors.left: label.right;
        anchors.right: parent.right;
        anchors.leftMargin: 4;
        anchors.verticalCenter: parent.verticalCenter;

        onActivated: root.indexChanged(index);
        onRenameOption: root.renameOption(newName);
        onAddOption: root.addOption();
        onRemoveOption: root.removeOption();
    }
}
