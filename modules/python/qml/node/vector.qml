import QtQuick 2.5
import QtQuick.Layouts 1.3

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.python.node 1.0 as Node

Node.Item
{
    anchors.leftMargin: 8;
    anchors.rightMargin: 8;

    height: 60;

    Column
    {
        id: col;

        anchors.left: parent.left;
        anchors.right: parent.right;

        Lib.Label
        {
            height: 24;
            anchors.left: parent.left;
            anchors.right: parent.right;
            text: param.name;
            font.pixelSize: 12;
        }

        RowLayout
        {
            height: 30;
            spacing: 4;

            anchors.left: parent.left;
            anchors.right: parent.right;

            InputField
            {
                Layout.fillWidth: true

                visible: param.dimension > 0;

                label.text: param.xLabel;
                input.text: param.x.toPrecision();
            }

            InputField
            {
                Layout.fillWidth: true

                visible: param.dimension > 1;

                label.text: param.yLabel;
                input.text: param.y.toPrecision();
            }

            InputField
            {
                Layout.fillWidth: true

                visible: param.dimension > 2;

                label.text: param.zLabel;
                input.text: param.z.toPrecision();
            }

            InputField
            {
                Layout.fillWidth: true

                visible: param.dimension > 3;

                label.text: param.wLabel;
                input.text: param.w.toPrecision();
            }
        }
    }
}
