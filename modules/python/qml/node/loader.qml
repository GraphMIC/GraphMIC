import QtQuick 2.5

Loader
{
    id: loader;

    property var param;

    anchors.left: parent ? parent.left : undefined;
    anchors.right: parent ? parent.right : undefined;

    Component
    {
        id: cBool;
        Bool { param: loader.param; }
    }

    Component
    {
        id: cNumber;
        Number { param: loader.param; }
    }

    Component
    {
        id: cString;
        String { param: loader.param; }
    }

    Component
    {
        id: cOption;
        Option { param: loader.param; }
    }

    Component
    {
        id: cDir;
        Dir { param: loader.param; }
    }

    Component
    {
        id: cFiles;
        Files { param: loader.param; }
    }

    Component
    {
        id: cVector;
        Vector { param: loader.param; }
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

    onParamChanged:
    {
        var type = param.componentType;

        if (type == 2)
        {
            loader.sourceComponent = cBool;
        }
        else if (type == 3)
        {
            loader.sourceComponent = cNumber;
        }
        else if (type == 4)
        {
            loader.sourceComponent = cString;
        }
        else if (type == 5)
        {
            loader.sourceComponent = cOption;
        }
        else if (type == 6)
        {
            loader.sourceComponent = cDir;
        }
        else if (type == 7)
        {
            loader.sourceComponent = cFiles;
        }
        else if (type == 8)
        {
            loader.sourceComponent = cVector;
        }
    }
}
