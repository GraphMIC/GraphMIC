import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Rectangle
{
    id: root;

    property alias model: repeater.model;
    property alias colors: colors;

    property string modelProperty;
    property string labelProperty;

    signal renameFinished(var tab, var input);
    signal tabClicked(var tab);
    signal closeTab(var tab);
    signal addTab();

    clip: true;
    color: "#21252B"
    height: 24;

    Item
    {
        id: colors;

        property alias text: text;
        property alias tab: tab;

        Item
        {
            id: text;

            property color normal: "#939CAA";
            property color active: "#fff";
        }

        Item
        {
            id: tab;

            property alias background: background;
            property alias border: border;

            Item
            {
                id: background;

                property color normal: "#21252B";
                property color active: "#3C424F"
            }

            Item
            {
                id: border;

                property color normal: "#3C424F";
                property color active: "#3C424F"
            }
        }
    }

    Row
    {
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;

        Repeater
        {
            id: repeater;

            delegate: Rectangle
            {
                id: delegate;

                property var modelItem: model[modelProperty];

                anchors.top: parent.top;
                anchors.bottom: parent.bottom;
                anchors.bottomMargin: -radius;

                width: row.width + 16;
                radius: 3;
                color: modelItem.active ? colors.tab.background.active : colors.tab.background.normal;
                border.color: modelItem.active ? colors.tab.border.active : colors.tab.border.normal;

                Lib.MouseArea
                {
                    id: maTab;

                    anchors.fill: parent;
                    onClicked: root.tabClicked(delegate);
                }

                Row
                {
                    id: row;

                    anchors.centerIn: parent;
                    spacing: 6;

                    Rectangle
                    {
                        anchors.verticalCenter: parent.verticalCenter;

                        width: 8;
                        height: width;
                        radius: width/2;
                        color: modelItem.active ? modelItem.modified ? "#3385ff" : "#8697A9" : "#00000000"
                        border.color: modelItem.active ? "#29313A" : modelItem.modified ? "#3385ff" : "#8697A9";
                    }

                    Lib.TabLabel
                    {
                        anchors.verticalCenter: parent.verticalCenter;
                        textColor: modelItem.active ? colors.text.active : colors.text.normal;
                        text: modelItem[labelProperty];
                        onInputFinished: root.renameFinished(delegate, newText);
                    }

                    Lib.IconButton
                    {
                        anchors.verticalCenter: parent.verticalCenter;
                        type: types.fa_times;
                        pixelSize: 10;
                        onClicked: root.closeTab(delegate);
                    }
                }
            }
        }
    }

    Item
    {
        id: iconView;

        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.margins: 2;

        width: 26

        Lib.Icon
        {
            id: icon;

            anchors.centerIn: parent;
            type: types.fa_plus;
            color: maIcon.containsMouse ? "#fff" : "#939CAA";
            pixelSize: 10;
        }

        Lib.MouseArea
        {
            id: maIcon;

            anchors.fill: parent;
            onClicked: root.addTab();
        }
    }

    Lib.Edge
    {
        align: sides.bottom;
        color: "#3C424F"
    }
}
