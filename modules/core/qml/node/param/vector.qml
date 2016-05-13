import QtQuick 2.5
import QtQuick.Layouts 1.3

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.core.node.param 1.0 as Param

Column
{
    id: root;

    property var param;
    property var focusView;
    property bool isDetail: false;
    property int entries: Math.min(4, param.labels.length);

    anchors.topMargin: 19;

    Lib.Label
    {
        anchors.left: parent.left;
        anchors.right: parent.right;
        text: param.name;
        font.pixelSize: root.isDetail ? 10 : 12;
    }

    RowLayout
    {
        height: 30;
        spacing: 4;

        anchors.left: parent.left;
        anchors.right: parent.right;

        Param.TextInput
        {
            Layout.fillWidth: true

            anchors.left: undefined;
            anchors.right: undefined;

            node: param.node;
            focusView: root.focusView;
            visible: entries > 0;

            label.text: param.labels[0];
            input.text: param.x.toPrecision();

            input.validator: RegExpValidator
            {
                regExp: /[-+]?[0-9]*\.?[0-9]*/
            }

            onInputFinished: param.x = parseFloat(pInput);
        }


        Param.TextInput
        {
            Layout.fillWidth: true

            anchors.left: undefined;
            anchors.right: undefined;

            node: param.node;
            focusView: root.focusView;
            visible: entries > 1;

            label.text: visible ? param.labels[1] : "";
            input.text: param.y.toPrecision();

            input.validator: RegExpValidator
            {
                regExp: /[-+]?[0-9]*\.?[0-9]*/
            }

            onInputFinished: param.y = parseFloat(pInput);
        }

        Param.TextInput
        {
            Layout.fillWidth: true

            node: param.node;
            anchors.left: undefined;
            anchors.right: undefined;

            focusView: root.focusView;
            visible: entries > 2;

            label.text: visible ? param.labels[2] : "";
            input.text: param.z.toPrecision();

            input.validator: RegExpValidator
            {
                regExp: /[-+]?[0-9]*\.?[0-9]*/
            }

            onInputFinished: param.z = parseFloat(pInput);
        }

        Param.TextInput
        {
            Layout.fillWidth: true

            anchors.left: undefined;
            anchors.right: undefined;

            node: param.node;
            focusView: root.focusView;
            visible: entries > 3;

            label.text: visible ? param.labels[3] : "";
            input.text: param.w.toPrecision();

            input.validator: RegExpValidator
            {
                regExp: /[-+]?[0-9]*\.?[0-9]*/
            }

            onInputFinished: param.w = parseFloat(pInput);
        }
    }
}
