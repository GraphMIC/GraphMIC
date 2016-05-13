import QtQuick 2.5

import org.graphmic.app 1.0 as App
import org.graphmic.preview 1.0 as Preview
import org.graphmic.core.lib 1.0 as Lib

Column
{
    property var controller: App.instance.controllers.preview;
    property var node: controller.node;

    spacing: 8;

    Repeater
    {
        model: controller.imageOutputs;
        delegate: ImageView
        {
            slot: model.slot;
        }
    }

    Repeater
    {
        model: controller.numberOutputs;
        delegate: NumberView
        {
            slot: model.slot;
        }
    }

    Repeater
    {
        model: controller.vectorOutputs;
        delegate: VectorView
        {
            slot: model.slot;
        }
    }

    Repeater
    {
        model: controller.pointsetOutputs;
        delegate: PointsetView
        {
            slot: model.slot;
        }
    }
}
