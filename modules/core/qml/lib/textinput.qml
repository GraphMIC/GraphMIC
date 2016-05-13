import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
  id: root;

  signal inputFinished(var newText);
  signal inputConfirmed();
  signal inputCancelled();

  property alias text: qmlTextInput.text;
  property alias textColor: qmlTextInput.color;
  property alias textSize: qmlTextInput.font.pixelSize;
  property alias active: qmlTextInput.activeFocus;
  property alias validator: qmlTextInput.validator;
  property alias selectionColor: qmlTextInput.selectionColor;
  property alias selectedTextColor: qmlTextInput.selectedTextColor;
  property alias bold: qmlTextInput.font.bold;
  property int margin: 0;

  property var layouts: Lib.Layout.Enum;
  property int layout: layouts.center;
  property bool showBorder: false;
  property bool editOnClick: false;
  property color borderDefault: "#939CAA";

  width: qmlTextInput.width + 2;
  height: qmlTextInput.height + 2;
  color: "#00000000";
  border.color: showBorder ? qmlTextInput.activeFocus ? "#4F88FF" : borderDefault : "#00000000";
  radius: 2;

  function edit()
  {
    qmlTextInput.initialText = qmlTextInput.text;
    qmlTextInput.forceActiveFocus();
    qmlTextInput.selectAll();
  }

  TextInput
  {
    id: qmlTextInput;

    FontLoader  { id: loader; source: "fonts/roboto/Roboto-Regular.ttf"; }
    FontLoader  { source: "fonts/roboto/Roboto-Thin.ttf"; }
    FontLoader  { source: "fonts/roboto/Roboto-Light.ttf"; }
    FontLoader  { source: "fonts/roboto/Roboto-Medium.ttf"; }
    FontLoader  { source: "fonts/roboto/Roboto-Bold.ttf"; }
    FontLoader  { source: "fonts/roboto/Roboto-Black.ttf"; }

    color: "#939CAA"
    font.family: loader.name;
    font.pixelSize: 12;
    verticalAlignment: Text.AlignVCenter;
    selectionColor: root.selectionColor;
    selectedTextColor: root.selectedTextColor;
    anchors.margins: root.margin;

    anchors.centerIn: layout == layouts.center ? parent : undefined;
    anchors.verticalCenter: parent.verticalCenter;
    anchors.right: layout == (layouts.right || layouts.center) ? parent.right : undefined;
    anchors.left: layout == (layouts.left || layouts.center) ? parent.left : undefined;

    activeFocusOnPress: false;
    property string initialText: "";

    Keys.onPressed:
    {
      if (event.key == Qt.Key_Escape)
      {
        root.inputCancelled();
        root.inputFinished(initialText);
      }
      else if (event.key == Qt.Key_Enter || event.key ==  Qt.Key_Return)
      {
        root.inputConfirmed();
        root.inputFinished(text);
      }
      else if (event.key == Qt.Key_Up || event.key == Qt.Key_Down)
      {
        event.accepted = true;
      }
    }
  }

  Lib.MouseArea
  {
    anchors.fill: parent;
    hoverEnabled: true;

    onClicked:
    {
      if (editOnClick)
      {
        root.edit();
        mouse.accepted = true;
      }
      else
      {
        mouse.accepted = root.active;
      }
    }

    onDoubleClicked:
    {
      root.edit();
      mouse.accepted = true;
    }
  }

}
