import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.python.designer 1.0 as Designer
import org.graphmic.python.editor 1.0 as Editor

Rectangle
{
    id: container;

    color: "#282C34"
    clip: true;

    property var controller: App.instance.controllers.python;
    property var script: controller.script;
    property bool showDesigner: script && script.nodeScript;

    function activate()
    {
        editor.activate();
    }

    onShowDesignerChanged:
    {
        if (showDesigner)
        {
            splitView.expandRight(400);
        }
        else
        {
            splitView.collapseRight();
        }
    }

    Header
    {
        id: header;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
    }

    Lib.SplitView
    {
        id: splitView;

        anchors.left: parent.left;
        anchors.top: header.bottom;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;

        minRight: 300;
        minLeft: 300;
        label1: "Editor";
        label2: "Designer";
        resizeable: script && script.nodeScript;

        view1: Item
        {
            anchors.fill: parent;

            Lib.SplitView
            {
                id: consoleSplit;

                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.top: parent.top;
                anchors.bottom: footer.top;

                minRight: 200;
                minLeft: 200;
                label1: "Editor";
                label2: "Console";
                orientation: Qt.Vertical;

                view1: Item
                {
                    anchors.fill: parent;

                    Lib.TabView
                    {
                        id: tabs;

                        anchors.left: parent.left;
                        anchors.right: parent.right;
                        anchors.top: parent.top;

                        model: App.instance.controllers.python.scriptList;
                        modelProperty: "script";
                        labelProperty: "name";

                        onTabClicked: tab.modelItem.activate();
                        onCloseTab: tab.modelItem.remove();
                        onAddTab: App.instance.controllers.python.addNewScript();
                        onRenameFinished:
                        {
                            tab.modelItem.name = input;
                            editor.activate();
                        }
                    }

                    Editor.View
                    {
                        id: editor;

                        anchors.left: parent.left;
                        anchors.right: parent.right;
                        anchors.top: tabs.bottom;
                        anchors.bottom: parent.bottom;
                    }
                }

                view2: Editor.Console
                {
                    anchors.fill: parent;
                }

                Component.onCompleted:
                {
                    consoleSplit.collapseBottom();
                }
            }

            Editor.Footer
            {
                id: footer;

                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.bottom: parent.bottom;
            }
        }

        view2: Designer.View
        {
            anchors.fill: parent;
        }

        Component.onCompleted:
        {
            splitView.collapseRight();
        }
    }
}
