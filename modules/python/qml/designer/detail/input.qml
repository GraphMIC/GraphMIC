import QtQuick 2.5

Repeater
{
    property var obj;

    model: obj && obj.componentType == 0;
    delegate: Group
    {
        TextField
        {
            label.text: "name"
            input.text: obj.name;

            onInputFinished: obj.name = newText;
        }

        OptionField
        {
            label.text: "data type";
            dropdown.model: ["Image Data", "Number Data", "Vector Data", "Pointset Data"];
            dropdown.currentIndex: obj.dataTypeID;

            onIndexChanged: obj.dataTypeID = index;
        }

        BoolField
        {
            label.text: "data required";
            checkbox.checked: obj.required;

            onClicked: obj.required = !obj.required;
        }

        Component.onCompleted: parent.height = this.height;
    }
}
