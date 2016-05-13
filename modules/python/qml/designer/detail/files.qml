import QtQuick 2.5

Repeater
{
    property var obj;

    model: obj && obj.componentType == 7;
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
            label.text: "title"
            input.text: obj.title;
            onInputFinished: obj.title = newText;
        }

        TextField
        {
            label.text: "filter"
            input.text: obj.filter;
            onInputFinished: obj.filter = newText;
        }

        Component.onCompleted: parent.height = this.height;
    }
}
