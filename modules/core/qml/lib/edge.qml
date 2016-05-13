import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
	property var sides: Lib.Orientation.Orientation;
	property int align: sides.top;
	property int offset: 0;
	property int size: 1;

	anchors.left: (align == sides.right) ? undefined : parent.left;
	anchors.right: (align == sides.left) ? undefined : parent.right;
	anchors.top: (align == sides.bottom) ? undefined : parent.top;
	anchors.bottom: (align == sides.top) ? undefined : parent.bottom;

	anchors.topMargin: align == sides.top ? offset : 0;
	anchors.leftMargin: align == sides.left ? offset : 0;
	anchors.rightMargin: align == sides.right ? offset : 0;
	anchors.bottomMargin: align == sides.bottom ? offset : 0;

	color: "#42434f";

	width: size;
	height: size;
}
