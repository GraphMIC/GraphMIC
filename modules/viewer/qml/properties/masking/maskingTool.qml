import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.viewer.properties.masking 1.0 as Masking

import GM 1.0 as GM

ColumnLayout
{
  id: root
  anchors.left: parent.left
  anchors.right: parent.right
  anchors.leftMargin: 10
  anchors.rightMargin: 10
  Layout.bottomMargin: 10
  Layout.topMargin: 6

  GM.MaskingItem
  {
    id: maskingItem
    onEnabledChanged:
    {
      buttonGroup.current = null;
    }
  }

  Grid
  {
    anchors.left: parent.left
    anchors.right: parent.right
    enabled: maskingItem.enabled

    columns: 3
    spacing: 2

    ExclusiveGroup
    {
      id: buttonGroup
    }

    Masking.Button
    {
      text: "Add"
      exclusiveGroup: buttonGroup
      toolItem: maskingItem
    }

    Masking.Button
    {
      text: "Subtract"
      exclusiveGroup: buttonGroup
      toolItem: maskingItem
    }

    Masking.Button
    {
      text: "Correction"
      exclusiveGroup: buttonGroup
      toolItem: maskingItem
    }

    Masking.Button
    {
      id: paintButton
      text: "Paint"
      exclusiveGroup: buttonGroup
      toolItem: maskingItem
    }

    Masking.Button
    {
      id: wipeButton
      text: "Wipe"
      exclusiveGroup: buttonGroup
      toolItem: maskingItem
    }

    Masking.Button
    {
      text: "Fill"
      exclusiveGroup: buttonGroup
      toolItem: maskingItem
    }

    Masking.Button
    {
      text: "Erase"
      exclusiveGroup: buttonGroup
      toolItem: maskingItem
    }
  }

  Lib.Label
  {
    text: "Brush Size:"
    visible: (wipeButton.checked || paintButton.checked) ? true : false
  }

  Lib.Slider
  {
    id: slider

    enabled: maskingItem.sliderEnabled
    visible: (wipeButton.checked || paintButton.checked) ? true : false

    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: 10
    anchors.rightMargin: 10

    maximumValue: 50
    minimumValue: 1

    onValueChanged: maskingItem.sliderSize = value;
  }
}
