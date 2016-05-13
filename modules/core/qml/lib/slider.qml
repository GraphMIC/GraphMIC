import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Slider
{
  id: root

  property color barColor: "gray"
  property color barHighlightColor: "lightblue"
  property color borderColor: "gray"
  property color handlePressedColor: "white"
  property color handleColor: "lightgray"
  property int handleSize: 10

  value: 0

  style: SliderStyle {
    groove: Rectangle {
      implicitWidth: 20
      implicitHeight: 4
      color: root.barColor
      radius: 3
      Rectangle {
        height: parent.height
        width: styleData.handlePosition
        implicitHeight: 6
        implicitWidth: 100
        radius: height/2
        color: root.barHighlightColor
      }
    }
    handle: Rectangle {
      anchors.centerIn: parent
      color: control.pressed ? root.handlePressedColor : root.handleColor
      border.color: root.borderColor
      border.width: 1
      implicitWidth: root.handleSize
      implicitHeight: root.handleSize
      radius: 2
    }
  }
}