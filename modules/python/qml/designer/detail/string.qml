import QtQuick 2.5

Repeater
{
    property var obj;

    model: obj && obj.componentType == 4
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
            input.text: obj.value;
            onInputFinished: obj.value = newText;
        }

        Component.onCompleted: parent.height = this.height;
    }
}
