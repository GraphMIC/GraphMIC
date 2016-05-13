import QtQuick 2.5
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib

ColumnLayout
{
  id: root;

  anchors.left: parent.left;
  anchors.right: parent.right;
  spacing: 0

  property color headerBackground: "#4B5051";
  property var body: undefined;
  property alias title: label.text;
  property bool expanded: true;
  property color colLab: "#7D8285";
  property int animT: 60;
  property bool isExpandable: true;

  onExpandedChanged: if (body) body.visible = expanded;

  Rectangle
  {
    id: bar
    anchors.left: parent.left
    anchors.right: parent.right
    height: 27
    gradient: Gradient
    {
      GradientStop { position: 0.0; color: "#323741" }
      GradientStop { position: 0.1; color: "#282C34" }
    }

    Rectangle
    {
      anchors.top: parent.top
      anchors.left: parent.left
      anchors.right: parent.right
      height: 1
      color: "#4C4C4C"
    }

    Lib.IconButton
    {
      id: btn;
      anchors.left: parent.left;
      anchors.leftMargin: 8;
      anchors.verticalCenter: parent.verticalCenter;

      type: types.fa_angle_right;
      color: isExpandable ? "white" : "transparent";
      rotation: root.expanded ? 90 : 0;

      Behavior on rotation { PropertyAnimation { duration: root.animT / 2; } }

      onClicked:
      {
        if(isExpandable)
          root.expanded = !root.expanded;
      }

    }

    Lib.Label
    {
      id: label;
      anchors.left: btn.right;
      anchors.verticalCenter: parent.verticalCenter;
      anchors.leftMargin: 3

      text: "Data Manager";
      color: "white"

      /*
      style: Text.Sunken
      font.capitalization: Font.AllUppercase
      font.weight: Font.DemiBold

      color: root.colLab
      */
    }
  }

  Rectangle
  {
    anchors.left: parent.left
    anchors.right: parent.right
    height: 1
    color: "#1E1E1E"
  }

  onBodyChanged:
  {
    if (body)
    {
      body.parent = root;
    }
  }
}
