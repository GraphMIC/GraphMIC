import QtQuick 2.4
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.viewer 1.0 as Viewer
import org.graphmic.viewer.properties.datamanager 1.0 as ViewItem
import org.graphmic.viewer.visualization 1.0 as ViewItem
import org.graphmic.viewer.properties 1.0 as ViewItem
import org.graphmic.app 1.0 as App

Item
{
  id: root;
  property var controller: App.instance.controllers.viewer

  onVisibleChanged:
  {
    if(visible)
    {
      controller.updateBoundingObjects()
    }
  }

  Rectangle
  {
    id: gmDatamanager
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    color: "#21252B"
    width: 290

    Viewer.ExternalViewerHeader
    {
      id: gmDatamanagerBar
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.top: parent.top
      text: "Data Manager"
    }

    ViewItem.DataManager
    {
      anchors.top: gmDatamanagerBar.bottom
      anchors.right: parent.right
      anchors.left: parent.left
      anchors.bottom: parent.bottom
    }
  }

  Rectangle
  {
    id: gmProperties
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    color: "#21252B"
    width: 290

    Viewer.ExternalViewerHeader
    {
      id: gmPropertiesBar
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.top: parent.top
      text: "Properties"
    }

    Lib.ScrollView
    {
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.top: gmPropertiesBar.bottom
      anchors.bottom: parent.bottom
      clip: true

      contentItem:Flickable
      {
        contentHeight: props.height
        boundsBehavior: Flickable.StopAtBounds
        ViewItem.Properties
        {
          id: props
          anchors.left: parent.left
          anchors.right: parent.right
        }
      }
    }
  }

  Item
  {
    id: gmStdMultiItem
    anchors.left: gmDatamanager.right
    anchors.top: parent.top
    anchors.right: gmProperties.left
    anchors.bottom: parent.bottom

    Viewer.ExternalViewerHeader
    {
      id: gmStdMultiItemBar
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.top: parent.top
      text: "Visualization"
      leftDecoration: true
      rightDecoration: true
    }

    ViewItem.MultiItem
    {
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.top: gmStdMultiItemBar.bottom
      anchors.bottom: parent.bottom
    }
  }
}
