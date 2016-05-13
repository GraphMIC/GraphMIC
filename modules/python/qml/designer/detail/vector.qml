import QtQuick 2.5

Repeater
{
    id: root;

    property var obj;

    model: obj && obj.componentType == 8
    delegate: Group
    {
        property int dim: obj.dimension;

        OptionField
        {
            label.text: "type"
            dropdown.model: ["1D Vector", "2D Vector", "3D Vector", "4D Vector"];

            dropdown.currentIndex: obj.dimension - 1;

            onIndexChanged: obj.dimension = index + 1;
        }

        TextField
        {
            label.text: "name"
            input.text: obj.name;
            onInputFinished: obj.name = newText;
        }

        TextField
        {
            label.text: "x value"
            input.text: (obj.x).toPrecision();
            onInputFinished: obj.x = parseFloat(newText);
        }

        TextField
        {
            label.text: "y value"
            input.text: (obj.y).toPrecision();
            onInputFinished: obj.y = parseFloat(newText);

            visible: obj.dimension > 1;
        }

        TextField
        {
            label.text: "z value"
            input.text: (obj.z).toPrecision();
            onInputFinished: obj.z = parseFloat(newText);

            visible: obj.dimension > 2;
        }

        TextField
        {
            label.text: "w value"
            input.text: (obj.w).toPrecision();
            onInputFinished: obj.w = parseFloat(newText);

            visible: obj.dimension > 3;
        }

        TextField
        {
            label.text: "x label"
            input.text: obj.xLabel;
            onInputFinished: obj.xLabel = newText;
        }

        TextField
        {
            label.text: "y label"
            input.text: obj.yLabel;
            onInputFinished: obj.yLabel = newText;

            visible: obj.dimension > 1;
        }

        TextField
        {
            label.text: "z label"
            input.text: obj.zLabel;
            onInputFinished: obj.zLabel = newText;

            visible: obj.dimension > 2;
        }

        TextField
        {
            label.text: "w label"
            input.text: obj.wLabel;
            onInputFinished: obj.wLabel = newText;

            visible: obj.dimension > 3;
        }

        onDimChanged: {
            console.log("dim changed: " + dim);
            console.log("root.height: " + root.height);

            root.height = dim * 60;;
        }
        Component.onCompleted: parent.height = this.height;
    }
}
