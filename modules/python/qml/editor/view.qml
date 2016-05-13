import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    property var controller: App.instance.controllers.python;
    property var editor: controller.editor;
    property var script: controller.script;

    clip: true;

    function activate()
    {
        textEdit.forceActiveFocus();
    }

    onVisibleChanged:
    {
        if (visible)
        {
            activate();
        }
    }

    onScriptChanged:
    {
        if (script)
        {
            textEdit.text = script.text;
        } else {
            textEdit.text = "";
        }
    }

    Item
    {
        anchors.fill: parent;
        visible: script;

        Lib.MouseArea
        {
            anchors.fill: parent;
            onClicked:
            {
                root.activate();
            }
        }

        Lib.TextEdit
        {
            id: textEdit

            y: -scrollView.flickableItem.contentY;

            anchors.leftMargin: lines.width;
            anchors.left: parent.left;
            anchors.right: parent.right;
            font.pixelSize: editor.fontSize;

            Keys.onPressed: event.accepted = editor.onKeyPressed(event.key, event.modifiers, event.text);
        }

        Lib.ScrollView
        {
            id: scrollView;

            anchors.fill: parent;

            Column
            {
                id: lines;

                width: editor.fontSize * 3;

                Repeater
                {
                    model: textEdit.lineCount;

                    delegate: Text
                    {
                        width: lines.width;
                        textFormat:             Text.PlainText;
                        style:                  Text.Normal;
                        color:                  textEdit.line - 1 == index ? "#939CAA" : "#4B5363"
                        font.family:            textEdit.font.family;
                        font.pixelSize:         editor.fontSize;
                        verticalAlignment:      Text.AlignVCenter;
                        horizontalAlignment:    Text.AlignHCenter;

                        text: index + 1;
                    }
                }
            }
        }
    }

    Lib.Edge
    {
        align: sides.left;
        color: "#3C424F"
    }
    
    Connections
    {
      target: controller;

      onUpdateScript:
      {
        script.text = textEdit.text
      }
    }

    Component.onCompleted:
    {
        editor.document       = textEdit.textDocument;
        editor.selectionStart = Qt.binding(function() { return textEdit.selectionStart; });
        editor.selectionEnd   = Qt.binding(function() { return textEdit.selectionEnd; });
    }
}
