import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.test 1.0 as Test
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.core.sidebar 1.0 as Sidebar
import org.graphmic.core.notification 1.0 as Notification
import org.graphmic.core.node.editor 1.0 as NodeEditor

Rectangle
{
	id: root;

	width: 300;
	height: 400;
	color: "#21252B";

	property var controller: App.instance.controllers.test

	MouseArea
	{
		anchors.fill: parent;

		onClicked: root.forceActiveFocus();
	}

	Header
	{
		id: header;

		anchors.left: parent.left;
		anchors.right: parent.right;
		anchors.top: parent.top;
	}

	NodeEditor.GraphView
    {
		anchors.top: header.bottom;
		anchors.right: caseListView.left;
		anchors.left: unitListView.right;
		anchors.bottom: footer.top;

		interactive: false;
    }

	Notification.View
	{
		id: notifications;

		anchors.bottom: footer.top;
		anchors.left: unitListView.right;
	}

	Test.UnitListView
	{
		id: unitListView;

		anchors.left: parent.left;
		anchors.top: header.bottom;
		anchors.bottom: footer.top;

		width: 400;

		units: controller.units;
		caseList: caseListView;
	}

	Test.CaseListView
	{
		id: caseListView;

		anchors.top: header.bottom;
		anchors.bottom: footer.top;
		anchors.right: parent.right;

		width: 400;
	}

	Test.Footer
	{
		id: footer;
	}

	Component.onCompleted:
    {
        controller.init();
    }
}
