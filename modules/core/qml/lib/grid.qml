import QtQuick 2.5

Item
{
	id: root;

	property int gridSize: 20;
	property color gridColor: "white";
	property int gridWidth: 1;
	property int offsetX: 0;
	property int offsetY: 0;

	clip: true;

	Row
	{
		Repeater
		{
			model: root.width/root.gridSize + 1;

			Item
			{
				id: gridRow;

				width: root.gridSize;
				height: root.height;
				x: index * root.gridSize + 1 + root.offsetX;

				Rectangle
				{
					anchors.left: parent.left;
					anchors.top: parent.top;
					anchors.bottom: parent.bottom;

					width: root.gridWidth;
					color: root.gridColor;
				}
			}
		}
	}

	Column
	{
		Repeater
		{
			model: root.height/root.gridSize + 1;

			Item
			{
				id: gridCol;

				width: root.width;
				height: root.gridSize;
				y: index * root.gridSize + 1 + root.offsetY;

				Rectangle
				{
					width: root.width;
					height: root.gridWidth;

					color: root.gridColor;
				}
			}
		}
	}
}
