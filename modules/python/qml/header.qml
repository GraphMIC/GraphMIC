import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root;

    property var controller: App.instance.controllers.python;
    property var script: controller.script;

    height: 32;
    color: "#21252B"

    Lib.Edge { align: sides.bottom; color: "#17191F" }

    Row
    {
        height: parent.height;
        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: 4;
        spacing: 4;

        Icon
        {
            anchors.verticalCenter: parent.verticalCenter;
            label.text: "Load"
            icon.type: icon.types.fa_folder_open;
            enabled: controller.script;
            onClicked: controller.loadScript();
        }

        Icon
        {
            anchors.verticalCenter: parent.verticalCenter;
            label.text: "Save"
            icon.type: icon.types.fa_save;
            enabled: controller.script;
            onClicked: controller.saveScript();
        }

        Icon
        {
            anchors.verticalCenter: parent.verticalCenter;
            label.text: "Compile"
            enabled: controller.script;
            onClicked:
            {
              controller.script.compile();
            }

            visible: editor.script && !editor.script.nodeScript;
        }
    }

    Row
    {
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.rightMargin: 8;

        spacing: 8;

        Lib.Label
        {
            anchors.verticalCenter: parent.verticalCenter;

            text: "standalone script"
            color: script && script.nodeScript ? "#939CAA" : "#fff"

            Lib.MouseArea
            {
                anchors.fill: parent;

                onClicked:
                {
                    if (script)
                    {
                        script.nodeScript = false;
                    }
                }
            }
        }

        Lib.IconButton
        {
            anchors.verticalCenter: parent.verticalCenter;

            type: script && script.nodeScript ? types.fa_toggle_on : types.fa_toggle_off;
            enabled: script;

            onClicked:
            {
                if (script)
                {
                    script.nodeScript = !script.nodeScript;
                }
            }
        }

        Lib.Label
        {
            anchors.verticalCenter: parent.verticalCenter;
            text: "node script"
            color: script && script.nodeScript ? "#fff" : "#939CAA";

            Lib.MouseArea
            {
                anchors.fill: parent;

                onClicked:
                {
                    if (script)
                    {
                        script.nodeScript = true;
                    }
                }
            }
        }
    }
}
