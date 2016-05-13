import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.app 1.0 as App

Rectangle
{
	id: root;

	property var app: App.instance;
	property var notifications: app.controllers.notifications
	property var dbg: app.controllers.debug

	anchors.left: parent.left;
	anchors.right: parent.right;
	anchors.bottom: parent.bottom;
	height: 26;
	color: "#131518"

	Lib.Label
	{
		visible: app.debugBuild;
		anchors.left: parent.left;
		anchors.verticalCenter: parent.verticalCenter;
		anchors.leftMargin: 8;
		font.pixelSize: 10;
		font.bold: true;
		color: "#fff";
		text: "nodes [" + dbg.nodeCount + "] connections [" + dbg.connectionCount + "] " + "connectionViews [" + dbg.connectionViewCount + "] logic [" + dbg.logicCount + "] comps [" + dbg.compCount + "] data [" + dbg.dataCount + "] constraints [" + dbg.constraintCount + "] images [" + dbg.imageCount + "] notifications [" + dbg.notificationCount + "]";
	}

	Row
	{
		anchors.right: parent.right;
		anchors.rightMargin: 8;
		anchors.verticalCenter: parent.verticalCenter;

		spacing: 4;

		Lib.IconButton
		{
			anchors.verticalCenter: parent.verticalCenter;
			visible: app.debugBuild;
			type: types.fa_bug;
			onClicked: App.instance.controllers.debug.debugUI = ! App.instance.controllers.debug.debugUI;
		}


		Lib.Label
		{
			anchors.verticalCenter: parent.verticalCenter;
			text: "version " + app.version;
			color: "#fff";
			font.bold: true;
		}
	}
}
