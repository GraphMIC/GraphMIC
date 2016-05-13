import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4
import org.graphmic.core.lib 1.0 as Lib
import GM 1.0 as GM

GM.SliderNavigatorItem
{
  id: sliderNavigator

  anchors.left: parent.left
  anchors.right: parent.right
  anchors.leftMargin: 5
  anchors.rightMargin: 5

  property alias text: label.text

  RowLayout
  {
    anchors.fill: parent

    Lib.Label
    {
      id: label
      Layout.alignment: Qt.AlignLeft
      Layout.preferredWidth: 40
      anchors.verticalCenter: parent.verticalCenter
    }

    Lib.Slider
    {
      id: slider
      Layout.fillWidth: true
      anchors.verticalCenter: parent.verticalCenter


      onValueChanged:
      {
        sliderNavigator.value = value
      }
    }

    Lib.SpinBox
    {
      id: spinbox
      value: 0
      Layout.alignment: Qt.AlignRight
      anchors.verticalCenter: parent.verticalCenter

      onValueChanged:
      {
        sliderNavigator.value = value
      }
    }
  }

  onSync:
  {
    spinbox.value = sliderNavigator.value
    slider.value = sliderNavigator.value

    spinbox.minimumValue = sliderNavigator.min
    slider.minimumValue = sliderNavigator.min

    spinbox.maximumValue = sliderNavigator.max
    slider.maximumValue = sliderNavigator.max
  }
}
