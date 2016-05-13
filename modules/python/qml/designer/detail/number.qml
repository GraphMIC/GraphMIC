import QtQuick 2.5

Repeater
{
    property var obj;

    model: obj && obj.componentType == 3
    delegate: Group
    {
        TextField
        {
            label.text: "name"
            input.text: obj.name;
            onInputFinished: obj.name = newText;
        }

        TextField
        {
            label.text: "value"
            input.text: (obj.value).toPrecision();
            onInputFinished: obj.value = parseFloat(newText);
        }

        TextField
        {
            label.text: "min"
            input.text: (obj.min).toPrecision();
            onInputFinished: obj.min = parseFloat(newText);
        }

        TextField
        {
            label.text: "max"
            input.text: (obj.max).toPrecision();
            onInputFinished: obj.max = parseFloat(newText);
        }

        Component.onCompleted: parent.height = this.height;
    }
}
