import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.test 1.0 as Test
import org.graphmic.app 1.0 as App

Rectangle
{
	id: root;

	property var app: App.instance;
	property var controller: App.instance.controllers.test;
	property var dbg: App.instance.controllers.debug;

	anchors.left: parent.left;
	anchors.right: parent.right;
	anchors.bottom: parent.bottom;
	height: 26;
	color: "#131518"

	Lib.Label
	{
		anchors.left: parent.left;
		anchors.verticalCenter: parent.verticalCenter;
		anchors.leftMargin: 8;
		font.pixelSize: 10;
		font.bold: true;
		color: "#fff";
		text: "nodes [" + dbg.nodeCount + "] connections [" + dbg.connectionCount + "] " + "connectionViews [" + dbg.connectionViewCount + "] logic [" + dbg.logicCount + "] comps [" + dbg.compCount + "] data [" + dbg.dataCount + "] constraints [" + dbg.constraintCount + "] images [" + dbg.imageCount + "] notifications [" + dbg.notificationCount + "]";
	}
}
