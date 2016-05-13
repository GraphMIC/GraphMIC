import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.core.node.properties 1.0 as Properties

Item
{
    id: root;

    function activate()
    {
        graphView.activate();
    }

    onVisibleChanged:
    {
        if (visible)
        {
            activate();
        }
    }

    Header
    {
        id: header;

        anchors.left: parent.left;
        anchors.right: parent.right;
    }

    Lib.SplitView
    {
        id: splitView;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: parent.bottom;

        minRight: 200;
        minLeft: 200;
        label1: "Graph";
        label2: "Properties";

        view1: Item
        {
            anchors.fill: parent;

            Lib.TabView
            {
                id: tabview;

                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.top: parent.top;

                model: App.instance.controllers.nodeEditor.graphList;
                modelProperty: "graph";
                labelProperty: "name";

                onTabClicked: tab.modelItem.activate();
                onCloseTab: tab.modelItem.remove();
                onAddTab: App.instance.controllers.nodeEditor.createGraph();
                onRenameFinished: {
                    tab.modelItem.name = input;
                    graphView.activate();
                }
            }

            GraphView
            {
                id: graphView;

                anchors.left: parent.left;
                anchors.top: tabview.bottom;
                anchors.right: parent.right;
                anchors.bottom: parent.bottom;
            }
        }

        view2: Properties.View
        {
            anchors.fill: parent;
            focusView: graphView;
        }
    }

    Component.onCompleted:
    {
        splitView.collapseRight();
    }
}
