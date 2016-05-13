import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root;

    property string text;

    color: "#131518"

    height: col.height;

    Column
    {
        id: col;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.leftMargin: 4;
        anchors.rightMargin: 4;

        Lib.Label
        {
            anchors.left: parent.left;
            anchors.right: parent.right;

            text: "Output";
            font.bold: true;
            lineHeight: 1.5;
        }

        Rectangle
        {
            anchors.left: parent.left;
            anchors.right: parent.right;

            height: 1;
            color: "#3C424F"
        }

        Lib.Label
        {
            anchors.left: parent.left;
            anchors.right: parent.right;

            elide: Text.ElideNone;
            wrapMode: Text.WordWrap;

            lineHeight: 1.5;

            color: "#fff";
            text: root.text;
        }
    }

}
