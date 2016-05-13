import QtQuick 2.5
import QtQuick.Controls 1.4

import org.graphmic.app 1.0 as App
import org.graphmic.core.lib 1.0 as Lib

Column
{
    property var controller: App.instance.controllers.notifications

    anchors.right: parent.right;
    anchors.margins: 8;
    spacing: 4;
    visible: controller.visible;

    add: Transition
    {
        NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 160 }
        NumberAnimation { properties: "x"; from: -400; to: 0; duration: 160 }
    }

    Repeater
    {
        model: controller.entries;
        delegate: Entry
        {
            entry: model.entry;
        }
    }

    function add(exc)
    {
        controller.add(exc.message);
    }

    function clear()
    {
        controller.clear();
    }
}
