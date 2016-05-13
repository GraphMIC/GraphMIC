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
        input.text: param.value.toPrecision();
        input.validator: RegExpValidator
        {
            regExp: /[-+]?[0-9]*\.?[0-9]*/
        }

        onInputFinished: param.value = parseFloat(pInput);
    }
}
