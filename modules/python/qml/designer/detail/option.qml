import QtQuick 2.5

Repeater
{
    property var obj;

    model: obj && obj.componentType == 5
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
            label.text: "options";
            dropdown.interactive: true;
            dropdown.model: obj.options;
            dropdown.currentIndex: obj.index;

            property var activeIndex: obj.index;

            onActiveIndexChanged: dropdown.currentIndex = activeIndex;
            onIndexChanged: obj.index = index;
            onRenameOption: obj.changeOption(newName, dropdown.currentIndex);
            onAddOption: obj.addOption();
            onRemoveOption: obj.removeOption();
        }

        Component.onCompleted: parent.height = this.height;
    }
}
