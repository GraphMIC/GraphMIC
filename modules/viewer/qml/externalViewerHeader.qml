import QtQuick 2.4
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
  id: root
  property string text: "";
  property bool leftDecoration: false;
  property bool rightDecoration: false;

  anchors.top: parent.top
  anchors.left: parent.left
  anchors.right: parent.right
  height: 27

  gradient: Gradient
  {
    GradientStop { position: 0.0; color: "#323741" }
    GradientStop { position: 0.1; color: "#282C34" }
  }

  ColumnLayout
  {
    anchors.fill: parent

    Rectangle
    {
      Layout.alignment: Qt.AlignTop
      anchors.left: parent.left
      anchors.right: parent.right
      height: 1
      color: "#1E1E1E"
    }

    Row
    {
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.leftMargin: 12

      Lib.Label
      {
        id: label;
        Layout.alignment: Qt.AlignCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        text: root.text;
        color: "white"
        font.weight: Font.DemiBold
        /*
        style: Text.Sunken
        font.capitalization: Font.AllUppercase
        font.weight: Font.DemiBold
        color: "#7D8285"
        */
      }
    }

    Rectangle
    {
      Layout.alignment: Qt.AlignBottom
      anchors.left: parent.left
      anchors.right: parent.right
      height: 1
      color: "#1e1e1e"
    }
  }

  Rectangle
  {
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    visible: root.leftDecoration
    width: 1
    color: "#1E1E1E"
  }

  Rectangle
  {
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    visible: root.rightDecoration
    width: 1
    color: "#1E1E1E"
  }
}
