import QtQuick 2.5

Repeater
{
    property var obj;

    model: obj && obj.componentType == 2
    delegate: Group
    {
        TextField
        {
            label.text: "name"
            input.text: obj.name;

            onInputFinished: obj.name = newText;
        }

        BoolField
        {
            label.text: "value";
            checkbox.checked: obj.value;

            onClicked: obj.value = !obj.value;
        }

        Component.onCompleted: parent.height = this.height;
    }
}
