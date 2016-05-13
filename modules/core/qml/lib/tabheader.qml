import QtQuick 2.5

Item
{
    id: root;

    default property alias content: row.children;

    property color backgroundColor: "#3C424F"
    property int radius: 4;
    property int padding: 4;
    property int spacing: 4;

    Rectangle
    {
        anchors.fill: row;
        anchors.bottomMargin: - root.radius - 2;
        anchors.rightMargin: - root.padding;
        anchors.leftMargin: - root.padding;

        color: root.backgroundColor;
        radius: root.radius;
    }

    Row
    {
        id: row;

        anchors.top: parent.top;
        anchors.bottom: parent.bottom;

        x: root.padding;
        spacing: root.spacing;
    }
}
