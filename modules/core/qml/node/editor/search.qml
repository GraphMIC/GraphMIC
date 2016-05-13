import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
	id: root;

	property var controller: App.instance.controllers.nodeSearch;
	property var focusView: root.parent;

	width: 400
	height: col.height + 8;
	color: "#131518"
	border.color: "#8C9BAB"
	radius: 4;
	visible: input.active;

	function activate()
	{
		input.edit();
	}

	function focusEditor()
	{
		root.focusView.forceActiveFocus();
	}

	function show(x, y)
	{
		root.x = x + 20;
		root.y = y - 16;
		activate();
	}

	Column
	{
		id: col;

		anchors.left: parent.left;
		anchors.right: parent.right;
		anchors.margins: 4;

		y: 4;

		Lib.TextInput
		{
			id: input;

			anchors.left: parent.left;
			anchors.right: parent.right;
			anchors.leftMargin: 4;
			anchors.rightMargin: 4;

			layout: layouts.fill;

			bold: true;
			textColor: "#fff"
			selectionColor: "#fff";
			selectedTextColor: "#000"
			margin: 12;
			textSize: 13;

			onTextChanged: controller.query = text;
			onInputConfirmed: controller.processQuery();
			onInputFinished: focusEditor();

			Rectangle
			{
				anchors.fill: parent;
				anchors.leftMargin: -4;
				anchors.rightMargin: -4;
				color: "#00000000"
				border.color: "#8C9BAB";
				radius: 3;

				Lib.Label
				{
					anchors.right: parent.right;
					anchors.rightMargin: 4;
					anchors.verticalCenter: parent.verticalCenter;
					text: controller.matches.length;
				}
			}
		}

		Lib.ListView
		{
			anchors.left: parent.left;
			anchors.right: parent.right;

			clip: true;
			height: 280;
			model: controller.matches;

			delegate: SearchEntry
			{
				width: parent ? parent.width : 0;
				match: modelData;
				search: input;
			}
		}
	}

	Keys.onPressed:
	{
		if (event.key == Qt.Key_Escape)
		{
			focusEditor();
		}
	}
}
