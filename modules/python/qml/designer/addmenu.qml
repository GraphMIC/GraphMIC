import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Column
{
    id: root;

    spacing: 2;

    visible: activeFocus;

    property var node;

    function clearFocus()
    {
        root.parent.forceActiveFocus();
    }

    Lib.TextButton
    {
        width: parent.width;
        color: "#17191F"
        label.text: "input"

        onClicked:
        {
            node.addInput();
            clearFocus();
        }
    }

    Lib.TextButton
    {
        width: parent.width;
        color: "#17191F"
        label.text: "bool"

        onClicked:
        {
            node.addBoolParam();
            clearFocus();
        }
    }

    Lib.TextButton
    {
        width: parent.width;
        color: "#17191F"
        label.text: "number"

        onClicked:
        {
            node.addNumberParam();
            clearFocus();
        }
    }

    Lib.TextButton
    {
        width: parent.width;
        color: "#17191F"
        label.text: "vector"

        onClicked:
        {
            node.addVectorParam();
            clearFocus();
        }
    }

    Lib.TextButton
    {
        width: parent.width;
        color: "#17191F"
        label.text: "string"

        onClicked:
        {
            node.addStringParam();
            clearFocus();
        }
    }

    Lib.TextButton
    {
        width: parent.width;
        color: "#17191F"
        label.text: "option"

        onClicked:
        {
            node.addOptionParam();
            clearFocus();
        }
    }

    Lib.TextButton
    {
        width: parent.width;
        color: "#17191F"
        label.text: "file list"

        onClicked:
        {
            node.addFilesParam();
            clearFocus();
        }
    }

    Lib.TextButton
    {
        width: parent.width;
        color: "#17191F"
        label.text: "directory"

        onClicked:
        {
            node.addDirParam();
            clearFocus();
        }
    }

    Lib.TextButton
    {
        width: parent.width;
        color: "#17191F"
        label.text: "output"

        onClicked:
        {
            node.addOutput();
            clearFocus();
        }
    }
}
