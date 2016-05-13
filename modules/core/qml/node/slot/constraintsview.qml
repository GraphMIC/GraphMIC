import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib

Row
{
    property var components;

    Lib.Label
    {
        text: "uchar"
        color: components[0] == 0 ? "#444" : "#fff";
    }

    Lib.Label
    {
        text: "ushort"
        color: components[1] == 0 ? "#444" : "#fff";
    }

    Lib.Label
    {
        text: "uint"
        color: components[2] == 0 ? "#444" : "#fff";
    }

    Lib.Label
    {
        text: "char"
        color: components[3] == 0 ? "#444" : "#fff";
    }

    Lib.Label
    {
        text: "char"
        color: components[4] == 0 ? "#444" : "#fff";
    }

    Lib.Label
    {
        text: "uint"
        color: components[5] == 0 ? "#444" : "#fff";
    }

    Lib.Label
    {
        text: "ushort"
        color: components[6] == 0 ? "#444" : "#fff";
    }

    Lib.Label
    {
        text: "uchar"
        color: components[7] == 0 ? "#444" : "#fff";
    }
}
