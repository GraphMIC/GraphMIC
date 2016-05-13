import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.viewer.properties.datamanager 1.0 as DataManger
import GM 1.0 as GM

Lib.ScrollView
{
  property var dataManager: Module.controllers["Manager"];
  contentItem:Flickable
  {
    id: root
    clip: true
    contentHeight: elements.height
    boundsBehavior: Flickable.StopAtBounds

    Column
    {
      id: elements
      anchors.left: parent.left
      anchors.right: parent.right

      Repeater
      {
        id:list
        model: dataManager.model

        Column
        {
          id: listItem
          anchors.left: parent ? parent.left : undefined
          anchors.right: parent ? parent.right : undefined

          Rectangle
          {
            anchors.left: parent.left
            anchors.right: parent.right
            color: "#4C4C4C"
            height: 1
          }

          Rectangle
          {
            id: expandItem
            property bool expanded: true;
            anchors.left: parent.left
            anchors.right: parent.right
            height: 35

            color: model.decoration ? "#aa5896BB" : "#272C33";

            MouseArea
            {
              anchors.fill: parent
              onClicked:
              {
                dataManager.index  = index
              }
            }

            RowLayout
            {
              anchors.fill: parent
              anchors.leftMargin: 10

              spacing: 5
              height: parent.height

              Lib.IconButton
              {
                id: cb
                type: highlight ? types.fa_eye : types.fa_eye_slash;
                colorActive: "#F0F9FF"
                pixelSize: 14
                highlight: true
                anchors.verticalCenter: parent.verticalCenter

                onClicked:
                {
                  highlight = !highlight
                  dataManager.index  = index
                  dataManager.toggleVisibility(highlight)
                }
              }

              Item
              {
                Layout.leftMargin: 5
                Layout.fillWidth: true

                anchors.top: parent.top
                anchors.bottom: parent.bottom

                Lib.TextInput
                {
                  anchors.verticalCenter: parent.verticalCenter
                  text: model.display
                  editOnClick: false
                  layout: layouts.left;
                  textColor: "#fff"
                  onInputConfirmed: dataManager.changeNodeName(index, text);
                  onInputFinished: parent.forceActiveFocus();
                }
              }

              Lib.IconButton
              {
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: 8;
                anchors.verticalCenter: parent.verticalCenter;

                type: types.fa_angle_right;
                color: "#F0F9FF"
                rotation: expandItem.expanded ? 90 : 180;

                Behavior on rotation { PropertyAnimation { duration: 30; } }

                onClicked:
                {
                  expandItem.expanded = !expandItem.expanded;
                }
              }
            }
          }

          DataManger.Delegate
          {
            id: pointSetList
            anchors.left: parent.left
            anchors.right: parent.right
            listController: pointSetManager
            listLabel.text: "PointSet"
            visible: expandItem.expanded ? true: false

            GM.ListManager
            {
              id: pointSetManager
            }
          }

          DataManger.Delegate
          {
            anchors.left: parent.left
            anchors.right: parent.right
            listController: measurementManager
            listLabel.text: "Measurement"
            visible: expandItem.expanded ? true: false

            GM.ListManager
            {
              id: measurementManager
            }
          }

          DataManger.Delegate
          {
            anchors.left: parent.left
            anchors.right: parent.right
            listController: maskingManager
            listLabel.text: "Masking"
            visible: expandItem.expanded ? true: false

            GM.ListManager
            {
              id: maskingManager
            }
          }

          Rectangle
          {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color: "#1E1E1E"
          }

          Component.onCompleted:
          {
            pointSetManager.type = GM.ListManager.POINTSET;
            measurementManager.type = GM.ListManager.MEASUREMENT;
            maskingManager.type = GM.ListManager.MASKING;

            pointSetManager.init(index);
            measurementManager.init(index);
            maskingManager.init(index);
          }
        }
      }
    }
  }
}