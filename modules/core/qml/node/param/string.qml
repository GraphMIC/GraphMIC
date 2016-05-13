import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.core.node.param 1.0 as Param

Item
{
    property var param;
    property var focusView;
    property bool isDetail: false;

    height: component.height + 6;

    Param.TextInput
    {
        id: component;

        node: param.node;
        focusView: parent.focusView;
        label.text: param.name + ":";
        input.text: param.value;
        valid: param.valid;

        onInputFinished:
        {
            param.value = pInput;
        }
    }
}
