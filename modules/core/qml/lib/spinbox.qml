import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import org.graphmic.core.lib 1.0 as Lib

SpinBox
{
    id: root
    property color borderColor: "#1E1E1E";

    FontLoader  { id: loader; source: "fonts/roboto/Roboto-Regular.ttf"; }
    FontLoader  { source: "fonts/roboto/Roboto-Thin.ttf"; }
    FontLoader  { source: "fonts/roboto/Roboto-Light.ttf"; }
    FontLoader  { source: "fonts/roboto/Roboto-Medium.ttf"; }
    FontLoader  { source: "fonts/roboto/Roboto-Bold.ttf"; }
    FontLoader  { source: "fonts/roboto/Roboto-Black.ttf"; }

    style: SpinBoxStyle
    {
        id: spinStyle
        textColor: "#939CAA"
        font.pixelSize: 11;
        font.family: loader.name

        incrementControl:Item
        {
            implicitWidth: padding.right
            Lib.Icon
            {
                anchors.centerIn: parent
                anchors.verticalCenterOffset: 4
                type: types.fa_sort_up;
                color: "#939CAA";
                pixelSize: 10;
            }
        }

        decrementControl:Item
        {
            implicitWidth: padding.right
            Lib.Icon
            {
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -4
                type: types.fa_sort_down;
                color: "#939CAA";
                pixelSize: 10;
            }
        }

        background: Rectangle
        {
            implicitWidth: 70
            implicitHeight: 20
            border.width: 1
            border.color: root.borderColor

            gradient: Gradient
            {
                GradientStop { position: 0.0; color: "#323741" }
                GradientStop { position: 0.1; color: "#282C34" }
            }
            radius: 2
        }
    }
}
