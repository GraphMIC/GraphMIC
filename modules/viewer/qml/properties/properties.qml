import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.viewer.properties 1.0 as Properties
import org.graphmic.viewer.properties.dataManager 1.0 as Property
import org.graphmic.viewer.properties.masking 1.0 as Property
import org.graphmic.viewer.properties.measurement 1.0 as Property
import org.graphmic.viewer.properties.navigator 1.0 as Property
import org.graphmic.viewer.properties.nodeProperties 1.0 as Property
import org.graphmic.viewer.properties.pointSet 1.0 as Property
import org.graphmic.viewer.properties.statistics 1.0 as Property
import org.graphmic.viewer.properties.volume 1.0 as Property

import GM 1.0 as GM

Column
{
  id: root

  property var controller: Module.controllers["PropertyController"];

  Properties.Item
  {
    title: "Node Properties"
    expanded: true
    visible: true

    body: Property.NodeProperties
    {
      anchors.left: parent.left
      anchors.right: parent.right
    }
  }

  Properties.Item
  {
    title: "Volume Rendering"
    expanded: true
    visible: controller.volumeRendering

    body: Property.VolumeVisualization
    {
      anchors.left: parent.left
      anchors.right: parent.right
    }
  }

  Properties.Item
  {
    title: "Image Navigator"
    expanded: true
    visible: controller.imageNavigator

    body: Property.ImageNavigator
    {
      anchors.left: parent.left
      anchors.right: parent.right
    }
  }

  Properties.Item
  {
    title: "Measurement"
    expanded: true
    visible: controller.measurement

    body: Property.MeasurementTool
    {
      anchors.left: parent.left
      anchors.right: parent.right
    }
  }

  Properties.Item
  {
    title: "PointSet"
    expanded: true
    visible: controller.pointSet

    body: Property.PointSetTool
    {
      anchors.left: parent.left
      anchors.right: parent.right
    }
  }

  Properties.Item
  {
    title: "Masking"
    expanded: true
    visible: controller.masking

    body: Property.MaskingTool
    {
      anchors.left: parent.left
      anchors.right: parent.right
    }
  }

  Properties.Item
  {
    title: "Statistics"
    visible: controller.statistics

    body: Property.ImageStatisticsTool
    {
      anchors.left: parent.left
      anchors.right: parent.right
    }
  }
}
