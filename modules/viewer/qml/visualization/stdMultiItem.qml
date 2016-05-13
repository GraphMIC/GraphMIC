import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import org.graphmic.core.lib 1.0 as Lib
import org.graphmic.viewer.visualization 1.0 as Visualization
import GM 1.0 as GM

Rectangle
{
    id: root;
    property color splitColor: "#4C4C4C";

    color: "#282C34"
    border.width: 1
    border.color: "#1E1E1E"

    GM.StdMultiItem
    {
        id: stdmultiItem
    }

    Visualization.Toolbar
    {
        id: toolbar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        multiItem: stdmultiItem
        anchors.leftMargin: 1
        anchors.rightMargin: 1
    }

    Item
    {
        anchors.top: toolbar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        clip: true

        GM.SliderLevelWindowItem
        {
            id: levelWindow
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            width: 50
            color: "#4C4C4C"
            borderColor: "transparent"
            fontSize: 9
            fontColor: "white"

            onEnabledChanged:
            {
                if(enabled)
                levelWindow.width = 50
                else
                levelWindow.width = 0
            }

            Behavior on width
            {
                PropertyAnimation
                {
                    duration: 120
                }
            }

            Rectangle
            {
                id: window
                border.width: 1
                border.color: "#1E1E1E"
                color: "#21252B"

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 3
                height: window_field.height


                Lib.TextInput
                {
                    id: window_field
                    anchors.fill: parent

                    text: ""

                    Keys.onPressed:
                    {
                        if (event.key == Qt.Key_Enter || event.key == Qt.Key_Return)
                        {
                            levelWindow.window = text
                        }
                    }
                }
            }

            Rectangle
            {
                id: level

                border.width: 1
                border.color: "#1E1E1E"
                color: "#21252B"

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: window.top
                anchors.margins: 3
                height: level_field.height

                Lib.TextInput
                {
                    id: level_field
                    anchors.fill: parent

                    text: ""

                    Keys.onPressed:
                    {
                        if (event.key == Qt.Key_Enter || event.key == Qt.Key_Return)
                        {
                            levelWindow.level = text
                        }
                    }
                }
            }
        }

        Connections
        {
            target: levelWindow;

            onSync:
            {
                window_field.text = levelWindow.window;
                level_field.text = levelWindow.level;
            }
        }

        SplitView
        {
            id: splitView
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: levelWindow.left
            anchors.bottom: parent.bottom
            orientation: Qt.Vertical

            handleDelegate: Rectangle
            {
                width: 7
                height: 7
                gradient: Gradient
                {
                    GradientStop { position: 0.0; color: "#323741" }
                    GradientStop { position: 0.1; color: "#282C34" }
                }
            }

            SplitView
            {
                height: parent.height/2
                orientation: Qt.Horizontal

                handleDelegate: Rectangle
                {
                    width: 7
                    height: 7
                    color: "#282C34"
                }

                Rectangle
                {
                    width: parent.width/2
                    color: "#21252B"
                    border.width: 1
                    border.color: "#1E1E1E"


                    Rectangle
                    {
                        anchors.fill: parent
                        color: "black"
                        border.width: 1
                        border.color: "#aa4C4C4C"
                        anchors.margins: 5

                        GM.RenderWindowItem
                        {
                            id: viewer_axial;
                            anchors.fill: parent
                            multiItem: stdmultiItem
                            clip: true
                            viewType: 0;

                            Component.onCompleted:
                            {
                                viewer_axial.setupView();
                            }

                            Text
                            {
                                anchors.left: parent.left
                                anchors.bottom: parent.bottom
                                anchors.leftMargin: 5
                                anchors.bottomMargin: 5
                                color: "#E15944"
                                text: "Axial"
                            }
                        }
                    }
                }

                Rectangle
                {
                    width: parent.width/2
                    color: "#21252B"
                    border.width: 1
                    border.color: "#1E1E1E"


                    Rectangle
                    {
                        anchors.fill: parent
                        color: "black"
                        border.width: 1
                        border.color: "#aa4C4C4C"
                        anchors.margins: 5

                        GM.RenderWindowItem
                        {
                            id: viewer_sagittal;

                            multiItem: stdmultiItem
                            anchors.fill: parent
                            viewType: 2;
                            clip: true

                            Component.onCompleted:
                            {
                                viewer_sagittal.setupView();
                            }

                            Text
                            {
                                anchors.left: parent.left
                                anchors.bottom: parent.bottom
                                anchors.leftMargin: 5
                                anchors.bottomMargin: 5
                                color: "#40B358"
                                text: "Sagittal"
                            }
                        }
                    }
                }
            }

            SplitView
            {

                height: parent.height/2
                orientation: Qt.Horizontal

                handleDelegate: Rectangle
                {
                    width: 7
                    height: 7
                    color: "#282C34"
                }

                Rectangle
                {
                    width: parent.width/2
                    color: "#21252B"
                    border.width: 1
                    border.color: "#1E1E1E"


                    Rectangle
                    {
                        anchors.fill: parent
                        color: "black"
                        border.width: 1
                        border.color: "#aa4C4C4C"
                        anchors.margins: 5

                        GM.RenderWindowItem
                        {
                            id: viewer_frontal;

                            multiItem: stdmultiItem
                            anchors.fill: parent
                            viewType: 1;
                            clip: true

                            Component.onCompleted:
                            {
                                viewer_frontal.setupView();
                            }

                            Text
                            {
                                anchors.left: parent.left
                                anchors.bottom: parent.bottom
                                anchors.leftMargin: 5
                                anchors.bottomMargin: 5
                                color: "#0250AB"
                                text: "Coronal"
                            }
                        }
                    }
                }

                Rectangle
                {
                    width: parent.width/2
                    color: "#21252B"
                    border.width: 1
                    border.color: "#1E1E1E"


                    Rectangle
                    {
                        anchors.fill: parent
                        gradient: Gradient
                        {
                            GradientStop { position: 0.0; color: "#282C34" }
                            GradientStop { position: 1.0; color: "#323741" }
                        }
                        border.width: 1
                        border.color: "#aa4C4C4C"
                        anchors.margins: 5
                        GM.RenderWindowItem
                        {
                            id: viewer_default;

                            multiItem: stdmultiItem
                            anchors.fill: parent
                            viewType: 3;
                            clip: true

                            Component.onCompleted:
                            {
                                viewer_default.setupView();
                            }

                            Text
                            {
                                anchors.left: parent.left
                                anchors.bottom: parent.bottom
                                anchors.leftMargin: 5
                                anchors.bottomMargin: 5
                                color: "#F0CA3E"
                                text: "3D"
                            }
                        }
                    }
                }
            }
        }

        Component.onCompleted:
        {
            stdmultiItem.init()
        }
    }
}
