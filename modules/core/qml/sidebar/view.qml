import QtQuick 2.5
import QtQuick.Controls 1.4

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root;

    anchors.left: parent.left;
    anchors.bottom: parent.bottom;
    anchors.top: parent.top;

    width: 45;
    color: "#21252B";

    property var context: App.instance.controllers.context;
    property var sidebarController: App.instance.controllers.sidebar;

    Column
    {
        id: header;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;

        Section
        {
            label.text: "Graph";
            icon.type: icon.types.fa_random;
            highlight: context.graph.visible;

            onClicked: context.setGraphContext();
        }

        Section
        {
            label.text: "Python";
            icon.type: icon.types.fa_code;
            highlight: context.python.visible;

            onClicked: context.setPythonContext();
        }

        Section
        {
            label.text: "Viewer";
            icon.type: icon.types.fa_image;
            highlight: context.viewer.visible;

            onClicked: context.setViewerContext();
        }
    }

    Column
    {
        id: footer;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        Section
        {
            property var notifications: App.instance.controllers.notifications;

            label.text: "Issues";
            icon.type: icon.types.fa_warning;
            highlight: notifications.visible;

            onClicked: notifications.visible = !notifications.visible;
        }

        Section
        {
            label.text: "Settings";
            icon.type: icon.types.fa_cog;
            highlight: context.settings.visible;

            onClicked: context.setSettingsContext();
        }
    }

    Lib.Edge { align: sides.right; color: "#17191F"; }
}
