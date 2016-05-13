import QtQuick 2.5

import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.python.designer 1.0 as Designer
import org.graphmic.python.designer.detail 1.0 as Detail

Lib.ScrollColumn
{
    id: root;

    property var node;

    Column
    {
        id: col;

        anchors.left: parent.left;
        anchors.right: parent.right;

        Detail.Loader
        {
            node: root.node;
        }
    }
}
