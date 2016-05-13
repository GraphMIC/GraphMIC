import QtQuick 2.4
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib
import GM 1.0 as GM

ColumnLayout
{
    spacing: 5
    property var controller: Module.controllers["NodePropertyController"];

    Column
    {
        Layout.topMargin: 5
        Layout.bottomMargin: 5
        anchors.left: parent.left
        anchors.right: parent.right

        Rectangle
        {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color: "#1E1E1E"
        }

        Rectangle
        {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color: "#4C4C4C"
        }
    }

    Row
    {
        spacing: 5

        Lib.TextButton
        {
            label.text: "DELETE NODE"
            label.color: "red"
            enabled: controller.enabled
            onClicked: controller.deleteNode();
        }

        Lib.TextButton
        {
            label.text: "ReInit"
            enabled: controller.enabled
            onClicked: controller.reinitNode();
        }
    }
}
