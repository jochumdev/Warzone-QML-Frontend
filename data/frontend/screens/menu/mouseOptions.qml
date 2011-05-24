import QtQuick 1.0
import "../../widgets" as Widgets

Item {
    id: mouseOptionsMenu

    width: parent.width
    height: parent.height

    Widgets.ImageButton {
        defaultSource: "image://imagemap/icon back"
        hoverSource: "image://imagemap/icon back hi"
        x: 5; y: 5
        onClicked: {
            mouseOptionsMenu.destroy();
            createMenu("optionsMenu");
        }
    }

    // Labels
    Column {
        id: labels
        width: 280
        anchors.top: parent.top
        anchors.topMargin: 56
        anchors.left: parent.left
        anchors.leftMargin: 30

        spacing: 15

        Widgets.LargeText { text: "Reverse Rotation" }
        Widgets.LargeText { height: 60;  text: "Trap Cursor" }
        Widgets.LargeText { text: "Switch Mouse Buttons" }
        Widgets.LargeText { text: "Rotate Screen" }
    }

    // Options
    Column {
        width: 165
        anchors.top: parent.top
        anchors.topMargin: 56
        anchors.left: labels.right

        spacing: 15
        Widgets.ClickSelect {width: parent.width; options: ["On", "Off"]}
        Widgets.ClickSelect {height: 60; width: parent.width; options: ["Off", "On"]}
        Widgets.ClickSelect {width: parent.width; options: ["Off", "On"]}
        Widgets.ClickSelect {width: parent.width; options: ["Right Mouse", "Middle Mouse"]}
    }
}