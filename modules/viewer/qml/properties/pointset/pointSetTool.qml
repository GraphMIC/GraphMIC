import QtQuick 2.5
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.viewer.properties.pointSet 1.0 as PointSet
import GM 1.0 as GM

ColumnLayout
{
  id: root
  anchors.left: parent.left
  anchors.right: parent.right
  Layout.bottomMargin: 10

  GM.PointListItem
  {
    id: pointListItem
  }

  Column
  {
    id: col
    anchors.left: parent.left
    anchors.right: parent.right

    Repeater
    {
      id: list
      model: pointListItem.pointListModel

      Rectangle
      {
        id: listItem
        width: col.width;
        color: "#21252B"
        height: 22

        RowLayout
        {
          anchors.fill: parent
          Rectangle
          {
            Layout.alignment : Qt.AlignLeft
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 4
            color: model.decoration ? "#aa5896BB" : "#1E1E1E";
          }

          Lib.Label
          {
            Layout.fillWidth: true
            Layout.leftMargin: 5
            text: model.display
            font.pixelSize: 10
            color: "#F0F9FF"
          }
        }

        MouseArea
        {
          anchors.fill: parent
          onClicked:
          {
            pointListItem.selectedIndex = index;
          }
        }
      }
    }
  }

  PointSet.Toolbar
  {
    id: toolbar
    anchors.right: parent.right
    anchors.left: parent.left
    pointList: pointListItem
  }
}
