import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Lib.Icon
{
	id: root;

	property bool highlight: false;

	property color colorDisabled: "#585D66";
	property color colorHovered: "#fff";
	property color colorActive: "#3385ff"
	property color colorNormal: "#939CAA";
	property int clickMargin: 0;

	color: !root.enabled ? colorDisabled : (ma.pressed || root.highlight) ? colorActive : ma.containsMouse ? colorHovered : colorNormal;

	signal clicked();

	Behavior on color
	{
		ColorAnimation
		{
			duration: 30;
		}
	}

	Lib.MouseArea
	{
		id: ma;

		anchors.fill: parent;
		anchors.margins: -root.clickMargin;
		hoverEnabled: true;

		onClicked:
		{
			root.clicked();
		}
	}
}
