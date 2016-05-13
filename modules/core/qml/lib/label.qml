import QtQuick 2.5

Text
{
	id: label;

	FontLoader  { id: loader; source: "fonts/roboto/Roboto-Regular.ttf"; }
	FontLoader  { source: "fonts/roboto/Roboto-Thin.ttf"; }
	FontLoader  { source: "fonts/roboto/Roboto-Light.ttf"; }
	FontLoader  { source: "fonts/roboto/Roboto-Medium.ttf"; }
	FontLoader  { source: "fonts/roboto/Roboto-Bold.ttf"; }
	FontLoader  { source: "fonts/roboto/Roboto-Black.ttf"; }

	elide: Text.ElideRight;
	textFormat: Text.PlainText;
	style: Text.Normal;
	color: enabled ? "#939CAA" :  "#585D66";
	font.family: loader.name;
	font.pixelSize: 12;
	verticalAlignment: Text.AlignVCenter;
}
