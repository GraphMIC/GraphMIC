import QtQuick 2.5

Repeater
{
    property var obj;

    model: obj && obj.componentType == 6
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
            label.text: "dialog title"
            input.text: obj.title;
            onInputFinished: obj.title = newText;
        }

        Component.onCompleted: parent.height = this.height;
    }
}
