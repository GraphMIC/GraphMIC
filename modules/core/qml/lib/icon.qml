import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Item
{
    id: root;

    property string type: "-";
    property var types: Lib.Icons.Icon;
    property int pixelSize: 14;
    property alias color: inner.color;
    property alias element: inner;

    width: Math.max(inner.width, inner.height);
    height: Math.max(inner.height, inner.height);

    Text
    {
        id: inner;

        FontLoader
        {
            id: fontLoader;
            source: "fonts/font-awesome/fontawesome-webfont.ttf";
        }

        anchors.centerIn:       parent;
        textFormat:             Text.PlainText;
        style:                  Text.Normal;
        color:                  "#fff"
        font.family:            fontLoader.name;
        verticalAlignment:      Text.AlignVCenter;
        text:                   root.type;
        font.pixelSize:         root.pixelSize;
    }
}
