import QtQuick 2.5
import QtQuick.Controls 1.4

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.python.designer.detail 1.0 as Detail

Rectangle
{
    id: root;

    property var focusView;
    property var pyController: App.instance.controllers.python;
    property var node: controller.node;
    property real alpha: 1;

    clip: true;

    color: "#21252B";

    Lib.MouseArea
    {
        id: ma;

        anchors.fill: parent;
        hoverEnabled: true;
        propagateComposedEvents: false;
        onPressed: root.forceActiveFocus();
    }

    TitleSection
    {
        id: header;

        title: "Designer"
    }

    Preview
    {
        id: desg;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: details.top;

        designer: pyController.designer;
    }

    Detail.View
    {
        id: details;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        height: 180;

        node: pyController.designer.node;
    }
}
