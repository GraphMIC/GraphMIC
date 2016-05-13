import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.viewer.properties.measurement 1.0 as Measurement
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

  GM.MeasurementItem
  {
    id: tool
  }

  Grid
  {
    columns: 2
    spacing: 3
    enabled: tool.enabled

    ExclusiveGroup { id: buttonGroup }

    Measurement.Button
    {
      text: "Draw Line"
      exclusiveGroup: buttonGroup
      onClicked: tool.actionDrawLineTriggered(checked)
    }

    Measurement.Button
    {
      text: "Draw Path"
      exclusiveGroup: buttonGroup
      onClicked: tool.actionDrawPathTriggered(checked)
    }

    Measurement.Button
    {
      text: "Draw Angle"
      exclusiveGroup: buttonGroup
      onClicked: tool.actionDrawAngleTriggered(checked);
    }

    Measurement.Button
    {
      text: "Draw Four Point Angle"
      exclusiveGroup: buttonGroup
      onClicked: tool.actionDrawFourPointAngleTriggered(checked);
    }

    Measurement.Button
    {
      text: "Draw Circle"
      exclusiveGroup: buttonGroup
      onClicked: tool.actionDrawCircleTriggered(checked);
    }

    Measurement.Button
    {
      text: "Draw Ellipse"
      exclusiveGroup: buttonGroup
      onClicked: tool.actionDrawEllipseTriggered(checked);
    }

    Measurement.Button
    {
      text: "Draw Double Ellipse"
      exclusiveGroup: buttonGroup
      onClicked: tool.actionDrawDoubleEllipseTriggered(checked);
    }

    Measurement.Button
    {
      text: "Draw Rectangle"
      exclusiveGroup: buttonGroup
      onClicked: tool.actionDrawRectangleTriggered(checked);
    }

    Measurement.Button
    {
      text: "Draw Polygon"
      exclusiveGroup: buttonGroup
      onClicked: tool.actionDrawPolygonTriggered(checked);
    }

    Measurement.Button
    {
      text: "Draw Bezier Curve"
      exclusiveGroup: buttonGroup
      onClicked: tool.actionDrawBezierCurveTriggered(checked);
    }

    Measurement.Button
    {
      text: "Draw Subdivision Polygon"
      exclusiveGroup: buttonGroup
      onClicked: tool.actionDrawSubdivisionPolygonTriggered(checked);
    }
  }

  Lib.Label
  {
    Layout.topMargin: 5
    anchors.left: parent.left
    anchors.right: parent.right

    visible: (text!="") ? true : false

    textFormat: Text.RichText
    text: tool.text
  }
}
