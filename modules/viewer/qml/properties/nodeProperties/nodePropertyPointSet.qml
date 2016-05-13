import QtQuick 2.4
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib
import GM 1.0 as GM

ColumnLayout
{
    spacing: 5

    Rectangle
    {
        Layout.topMargin: 5
        Layout.bottomMargin: 5
        anchors.left: parent.left
        anchors.right: parent.right

        color: "#1E1E1E"
        height: 1
    }

    Lib.Label
    {
        text: "PointSet"
    }

    Row
    {
        spacing: 5

        property var controller: Module.controllers["NodePropertyController"];

        Lib.TextButton
        {
            label.text: "Load"
            onClicked: controller.loadPointSet();
        }

        Lib.TextButton
        {
            label.text: "Save"
            onClicked: controller.savePointSet();
        }
    }
}
