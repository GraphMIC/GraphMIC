import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root;

    property var controller: App.instance.controllers.python;

    height: 100;
    color: "#21252B"

    Lib.Edge { align: sides.bottom; color: "#17191F" }

    Lib.ScrollView
    {
        id: scrollView;
        anchors.fill: parent;
        anchors.topMargin: 5
        anchors.leftMargin: 5
        contentItem: Lib.TextEdit
        {
            text: controller.script ? controller.script.output : ""
            textFormat: Text.AutoText
        }
    }
}
