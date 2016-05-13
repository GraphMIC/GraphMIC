import QtQuick 2.4
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib
import GM 1.0 as GM

ColumnLayout
{
  id: root
  Layout.topMargin: 6
  anchors.left: parent.left
  anchors.right: parent.right
  anchors.leftMargin: 10
  anchors.rightMargin: 10

  RowLayout
  {
    Lib.CheckBox
    {
      id: cbBinSize
      checked: true
      enabled: statisticItem.enabled

      onClicked:
      {
        checked = !checked
        statisticItem.defaultBinSize = checked
      }
    }

    Lib.Label
    {
      Layout.leftMargin: 10
      anchors.verticalCenter: parent.verticalCenter
      text: "Use Default Bin Size"
    }
  }

  RowLayout
  {
    visible: !cbBinSize.checked

    Lib.Label
    {
      text: "Bin Size"
      enabled: !cbBinSize.checked
      anchors.verticalCenter: parent.verticalCenter
    }

    Lib.SpinBox
    {
      enabled: !cbBinSize.checked

      Layout.leftMargin: 10
      anchors.verticalCenter: parent.verticalCenter
      value: 1
      maximumValue: 255
      minimumValue: 1

      onValueChanged:
      {
        statisticItem.binSize = value
      }
    }
  }

  GM.ImageStatisticsItem
  {
    id: statisticItem

    Layout.topMargin: 6
    anchors.left: parent.left
    anchors.right: parent.right

    height: 200

    GM.HistogramItem
    {
      id: histogram
      anchors.fill: parent
    }

    Component.onCompleted:
    {
      statisticItem.histogramItem =  histogram
    }
  }

  Column
  {
    anchors.left: parent.left
    anchors.right: parent.right
    Layout.bottomMargin: 10
    Lib.Label
    {
      textFormat: Text.RichText
      text: histogram.binInfo
    }

    Lib.Label
    {
      textFormat: Text.RichText
      text: statisticItem.histogramInfo
    }
  }

}
