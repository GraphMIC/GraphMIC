import QtQuick 2.5
import QtQuick.Layouts 1.3

import org.graphmic.core.lib 1.0 as Lib

Item
{
    property var param;
    property var focusView;
    property bool isDetail: false;

    height: 30;

    RowLayout
    {
        anchors.fill: parent;

        Lib.Label
        {
            id: label;

            anchors.verticalCenter: parent.verticalCenter;

            Layout.fillWidth: true;
            Layout.minimumWidth: 40;

            text: param.name;
        }

        Lib.DropDown
        {
            id: dd;

            anchors.verticalCenter: parent.verticalCenter;

            Layout.fillWidth: true;
            Layout.minimumWidth: 40;

            model: param.options;

            backgroundColor: root.isDetail ? "#282C34" : "#131518"
            currentIndex: param.index;

            onActivated:
            {
                param.index = index;
            }
        }
    }
}
