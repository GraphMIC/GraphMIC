import QtQuick 2.5
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.viewer.properties.volume 1.0 as Volume
import GM 1.0 as GM

ColumnLayout
{
  anchors.left: parent.left
  anchors.right: parent.right
  Layout.bottomMargin: 10

  spacing: 5

  GM.VolumeProperties
  {
    id: properties
  }

  Lib.CheckBox
  {
    id: cb_ren
    Layout.topMargin: 6
    anchors.left: parent.left
    anchors.leftMargin: 10

    checked: false
    enabled: false

    Lib.Label
    {
      anchors.left: parent.left
      anchors.verticalCenter: parent.verticalCenter
      anchors.leftMargin: 30
      color: cb_ren.enabled ? "white" : "#939CAA"
      text: "Volumerendering"
    }

    onClicked:
    {
      checked = !checked
      properties.rendering = checked
    }
  }

  Lib.CheckBox
  {
    id: cb_lod

    anchors.left: parent.left
    anchors.leftMargin: 10

    checked: false
    enabled: cb_ren.checked

    Lib.Label
    {
      anchors.left: parent.left
      anchors.verticalCenter: parent.verticalCenter
      anchors.leftMargin: 30
      color: cb_ren.checked ? "white" : "#939CAA"
      text: "Level of Detail"
    }

    onClicked:
    {
      checked = !checked
      properties.lod = checked
    }
  }

  Lib.DropDown
  {
    id: dd_mod;

    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: 10
    anchors.rightMargin: 10

    currentIndex: 0
    enabled: cb_ren.checked

    model: [
    "CPU raycast",
    "CPU MIP raycast",
    "GPU slicing",
    "GPU raycast",
    "GPU MIP raycast",
    ]

    onCurrentIndexChanged:
    {
      properties.mode = currentIndex
    }
  }

  Volume.TransferFunction
  {
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: 10
    anchors.rightMargin: 10

    visible: cb_ren.checked
  }


  Connections
  {
    target: properties;

    onSync:
    {
      dd_mod.currentIndex = properties.mode;
      //dd_mod.enabled = properties.enabled;

      cb_lod.checked = properties.lod;
      //cb_lod.enabled = properties.enabled;

      cb_ren.checked = properties.rendering;
      cb_ren.enabled = properties.enabled;
    }
  }
}
