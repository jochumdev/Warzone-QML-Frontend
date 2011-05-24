import QtQuick 1.0
import "../../widgets" as Widgets

Item {
    id: graphicsOptionsMenu

    width: parent.width
    height: parent.height

    Widgets.ImageButton {
        defaultSource: "image://imagemap/icon back"
        hoverSource: "image://imagemap/icon back hi"
        x: 5; y: 5
        onClicked: {
            graphicsOptionsMenu.destroy();
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

        Widgets.LargeText { text: "Video Playback" }
        Widgets.LargeText { text: "Scanlines" }
        Widgets.LargeText { text: "Screen Shake" }
        Widgets.LargeText { text: "Fog" }
        Widgets.LargeText { text: "Subtitles" }
        Widgets.LargeText { text: "Shadows" }
    }

    // Options
    Column {
        width: 165
        anchors.top: parent.top
        anchors.topMargin: 56
        anchors.left: labels.right

        spacing: 15
        Widgets.ClickSelect {width: parent.width; options: ["Fullscreen", "1X", "2X"]}
        Widgets.ClickSelect {width: parent.width; options: ["Off", "On"]}
        Widgets.ClickSelect {width: parent.width; options: ["Off", "On"]}
        Widgets.ClickSelect {width: parent.width; options: ["Mist", "Fog Of War"]}
        Widgets.ClickSelect {width: parent.width; options: ["On", "Off"]}
        Widgets.ClickSelect {width: parent.width; options: ["On", "Off"]}
    }
}
