import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Repeater
{
    property var node;

    model: node;
    delegate: Group
    {
        TextField
        {
            label.text: "name"
            input.text: node.name;
            onInputFinished: node.name = newText;
        }

        TextField
        {
            label.text: "doc link"
            input.text: node.docLink
            onInputFinished: node.docLink = newText;
        }

        BoolField
        {
            label.text: "runnable"
            checkbox.checked: node.runnable;

            onClicked: node.runnable = !node.runnable;
        }

        OptionField
        {
            label.text: "execute";
            dropdown.model: ["always", "only when modified"];
            enabled: node.runnable;

            onIndexChanged:
            {
                if (index == 0)
                {
                    node.forceExecution = true;
                }
                else
                {
                    node.forceExecution = false;
                }
            }
        }

        Component.onCompleted: parent.height = this.height;
    }
}
