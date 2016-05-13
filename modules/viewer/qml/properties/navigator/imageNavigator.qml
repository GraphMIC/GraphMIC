import QtQuick 2.4
import QtQuick.Controls 1.4
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.viewer.properties.navigator 1.0 as Navigator
import GM 1.0 as GM

GM.ImageNavigator
{
  id: imageNavigator

  anchors.margins: 10
  height: 150

  Row
  {
    id: worldCoordItem

    anchors.left: parent.left
    anchors.top: parent.top
    anchors.right: parent.right
    anchors.margins: 5
    spacing: 5

    Lib.SpinBox
    {
      id: worldCoordX
      decimals: 2
      borderColor: "#40B358"

      onValueChanged:
      {
        imageNavigator.worldCoordinateX = value
      }
    }

    Lib.SpinBox
    {
      id: worldCoordY
      decimals: 2
      borderColor: "#0250AB"

      onValueChanged:
      {
        imageNavigator.worldCoordinateY = value
      }
    }

    Lib.SpinBox
    {
      id: worldCoordZ
      decimals: 2
      borderColor: "#E15944"

      onValueChanged:
      {
        imageNavigator.worldCoordinateZ = value
      }
    }

    Lib.Label
    {
      text: "(mm)"
      anchors.verticalCenter: parent.verticalCenter
    }
  }

  Column
  {
    anchors.left: parent.left
    anchors.top: worldCoordItem.bottom
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.topMargin: 5

    spacing: -3

    Navigator.SubItem
    {
      id: navigator_axial
      height: parent.height/4

      text: "Axial"
    }

    Navigator.SubItem
    {
      id: navigator_sagittal
      height: parent.height/4

      text: "Sagittal"
    }

    Navigator.SubItem
    {
      id: navigator_cornal
      height: parent.height/4

      text: "Coronal"
    }

    Navigator.SubItem
    {
      id: navigator_time
      height: parent.height/4

      text: "Time"
    }
  }

  Component.onCompleted:
  {
    imageNavigator.navigatorAxial = navigator_axial;
    imageNavigator.navigatorSagittal = navigator_sagittal;
    imageNavigator.navigatorCoronal = navigator_cornal;
    imageNavigator.navigatorTime = navigator_time;

    imageNavigator.initialize()
  }

  onSync:
  {

    worldCoordX.value = imageNavigator.worldCoordinateX;
    worldCoordY.value = imageNavigator.worldCoordinateY;
    worldCoordZ.value = imageNavigator.worldCoordinateZ;

    worldCoordX.minimumValue = imageNavigator.worldCoordinateXMin;
    worldCoordY.minimumValue = imageNavigator.worldCoordinateYMin;
    worldCoordZ.minimumValue = imageNavigator.worldCoordinateZMin;

    worldCoordX.maximumValue = imageNavigator.worldCoordinateXMax;
    worldCoordY.maximumValue = imageNavigator.worldCoordinateYMax;
    worldCoordZ.maximumValue = imageNavigator.worldCoordinateZMax;

  }
}
