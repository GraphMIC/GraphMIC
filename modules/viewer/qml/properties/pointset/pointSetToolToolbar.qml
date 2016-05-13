import QtQuick 2.5
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.viewer.properties.pointSet 1.0 as PointSet

RowLayout
{
    id: root
    property bool enabled;
    property var pointList;

    anchors.leftMargin: 10
    anchors.rightMargin: 10

    Connections
    {
        target: pointList

        onPointEditChanged: addbtn.checked = pointList.pointEdit;
    }

    Row
    {
        spacing: -5
        Layout.alignment: Qt.AlignLeft

        PointSet.Button
        {
            id: addbtn
            text: "Add"
            toggle: true
            checked: false
            enabled: pointList.enabled

            onClicked: pointList.addPoint(checked)
        }

        PointSet.Button
        {
            text: "Delete"
            enabled: pointList.enabled

            onClicked: pointList.removeSelectedPoint()
        }
    }

    Row
    {
        spacing: -5
        Layout.alignment: Qt.AlignRight

        PointSet.Button
        {
            text: "Up"
            enabled: pointList.enabled
            onClicked: pointList.moveSelectedPointUp()
        }

        PointSet.Button
        {
            text: "Down"
            enabled: pointList.enabled
            onClicked: pointList.moveSelectedPointDown()
        }
    }
}
