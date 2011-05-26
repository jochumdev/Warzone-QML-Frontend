import QtQuick 1.0
import "../../widgets" as Widgets

Item {
    id: videoOptionsMenu

    width: parent.width
    height: parent.height

    Widgets.ImageButton {
        defaultSource: "image://imagemap/icon back"
        hoverSource: "image://imagemap/icon back hi"
        x: 5; y: 5
        onClicked: {
            videoOptionsMenu.destroy();
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
        Widgets.ClickSelect {
            width: parent.width;
            options: ["Fullscreen", "1X", "2X"]
            value: {
                var tmp = config.getValue("FMVmode");
                (tmp == 0 ? 0 : options.indexOf(tmp+"X"))
            }
            onValueChanged: config.setValue("fsaa", (value == 0 ? 0 : options[value].substr(0, options[value].length-1)))
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: ["Off", "On"]
            value: config.getValue("scanlines") ? 1 : 0;
            onValueChanged: config.setValue("scanlines", (value == 1))
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: ["Off", "On"]
            value: config.getValue("shake") ? 1 : 0;
            onValueChanged: config.setValue("shake", (value == 1))
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: ["Mist", "Fog Of War"]
            value: config.getValue("visfog") ? 1 : 0;
            onValueChanged: config.setValue("visfog", (value == 1))
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: ["Off", "On"]
            value: config.getValue("subtitles") ? 1 : 0;
            onValueChanged: config.setValue("subtitles", (value == 1))
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: ["Off", "On"]
            value: config.getValue("shadows") ? 1 : 0;
            onValueChanged: config.setValue("shadows", (value == 1))
        }
    }
}
