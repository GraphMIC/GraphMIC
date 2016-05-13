import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.core.sidebar 1.0 as Sidebar
import org.graphmic.core.notification 1.0 as Notification

Rectangle
{
	id: root;

	width: 300;
	height: 400;
	color: "#111"

	Sidebar.View
	{
		id: sidebar;

		anchors.top: parent.top;
		anchors.bottom: footer.top;
	}

	Context
	{
		anchors.left: sidebar.right;
		anchors.right: parent.right;
		anchors.top: parent.top;
		anchors.bottom: footer.top;
	}

	Notification.View
	{
		id: notifications;

		anchors.bottom: footer.top;
		anchors.left: sidebar.right;
	}

	App.Footer
	{
		id: footer;
	}
}
