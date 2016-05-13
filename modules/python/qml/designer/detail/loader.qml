import QtQuick 2.5

import org.graphmic.python.designer.detail 1.0 as Detail

Loader
{
    id: loader;

    property var node;
    property var obj: node ? node.selected : undefined;

    anchors.left: parent ? parent.left : undefined;
    anchors.right: parent ? parent.right : undefined;
    anchors.leftMargin: 8;
    anchors.rightMargin: 8;

    Component
    {
        id: cInput;
        Detail.Input { obj: loader.obj; }
    }

    Component
    {
        id: cOutput;
        Detail.Output { obj: loader.obj; }
    }

    Component
    {
        id: cBool;
        Bool { obj: loader.obj; }
    }

    Component
    {
        id: cNumber;
        Number { obj: loader.obj; }
    }

    Component
    {
        id: cString;
        String { obj: loader.obj; }
    }

    Component
    {
        id: cOption;
        Option { obj: loader.obj; }
    }

    Component
    {
        id: cDir;
        Dir { obj: loader.obj; }
    }

    Component
    {
        id: cFiles;
        Files { obj: loader.obj; }
    }

    Component
    {
        id: cVector;
        Vector { obj: loader.obj; }
    }

    Component
    {
        id: cError;
        Rectangle
        {
            color: "#ff0000";
            height: 30;
            Text { anchors.centerIn: parent; color: "#fff"; text: "invalid component!" }
        }
    }

    Component
    {
        id: cNode;
        Node { node: root.node; }
    }

    onObjChanged:
    {
        console.log("obj changed: " + obj)
        if (!node)
        {
            return;
        }

        if (!obj)
        {
            loader.sourceComponent = cNode;
            return;
        }

        var type = obj.componentType;

        if (type == 0)
            loader.sourceComponent = cInput;
        else if (type == 1)
            loader.sourceComponent = cOutput;
        else if (type == 2)
            loader.sourceComponent = cBool;
        else if (type == 3)
            loader.sourceComponent = cNumber;
        else if (type == 4)
            loader.sourceComponent = cString;
        else if (type == 5)
            loader.sourceComponent = cOption;
        else if (type == 6)
            loader.sourceComponent = cDir;
        else if (type == 7)
            loader.sourceComponent = cFiles;
        else if (type == 8)
            loader.sourceComponent = cVector;
        else
            loader.sourceComponent = cError;
    }
}
