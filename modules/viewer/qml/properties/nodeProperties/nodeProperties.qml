import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.viewer.properties.nodeProperties 1.0 as NodeProperties
import GM 1.0 as GM

Column
{
  id: root

  anchors.left: parent.left
  anchors.right: parent.right
  anchors.leftMargin: 10
  anchors.rightMargin: 10

  spacing: 5

  property var controller: Module.controllers["NodePropertyController"];

  Layout.bottomMargin: 10
  Layout.topMargin: 6

  Lib.Label
  {
    anchors.left: parent.left
    anchors.right: parent.right
    text: "Opacity"
  }

  RowLayout
  {
    anchors.left: parent.left
    anchors.right: parent.right

    Lib.Slider
    {
      id: opacitySlider
      Layout.alignment: Qt.AlignLeft
      Layout.fillWidth: true
      enabled: controller.enabled
      value: 0
      minimumValue: 0
      maximumValue: 100

      onValueChanged: controller.nodeOpacity = value;
    }

    Lib.Label
    {
      Layout.alignment: Qt.AlignRight
      text: parseInt(opacitySlider.value) + "%"
    }
  }


  Lib.Label
  {
    anchors.left: parent.left
    anchors.right: parent.right
    color: controller.enabled ? "white" : "#939CAA"
  }

  RowLayout
  {
    id: colorTab

    Rectangle
    {
      id: colorRect
      anchors.verticalCenter: parent.verticalCenter
      Layout.alignment: Qt.AlignLeft
      height: 15
      width: 20
      radius: 1
      border.width: 1
      border.color: "#1E1E1E"
    }


    Lib.TextButton
    {
      id: colorLabel
      Layout.alignment: Qt.AlignRight
      Layout.leftMargin: 5

      anchors.verticalCenter: parent.verticalCenter
      label.text: "Choose Color"
      label.color: controller.enabled ? "white" : "#939CAA"
      enabled: controller.enabled
      onClicked: controller.chooseColor()
    }
  }

  NodeProperties.PointSet
  {
    id: nodePropertyPointSet
    anchors.left: parent.left
    anchors.right: parent.right
    visible: false
  }

  NodeProperties.Masking
  {
    id: nodePropertyMasking
    anchors.left: parent.left
    anchors.right: parent.right
    visible: false
  }

  NodeProperties.General
  {
    anchors.left: parent.left
    anchors.right: parent.right
    visible: true
  }

  Connections
  {
    target: controller;

    onSync:
    {
      opacitySlider.value = controller.nodeOpacity;
      colorRect.color = controller.nodeColor;
    }

    onNodeColorChanged:
    {
      colorRect.color = controller.nodeColor;
    }

    onTypeChanged:
    {

      switch (controller.type)
      {
      case GM.ListManager.POINTSET:
        nodePropertyPointSet.visible = true;
        nodePropertyMasking.visible = false;
        break;
      case GM.ListManager.IMAGE:
        nodePropertyPointSet.visible = false;
        nodePropertyMasking.visible = false;
        break;
      case GM.ListManager.MASKING:
        nodePropertyPointSet.visible = false;
        nodePropertyMasking.visible = true;
        break;
      case GM.ListManager.MEASUREMENT:
        nodePropertyPointSet.visible = false;
        nodePropertyMasking.visible = false;
        break;
      default:
        nodePropertyPointSet.visible = false;
        nodePropertyMasking.visible = false;
        break;
      }
    }
  }
}
