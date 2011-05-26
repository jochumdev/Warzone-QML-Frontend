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

    Text {
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 50

        text: "* Takes effect on game restart"
        color: "white"
        smooth: true
        font.family: "DejaVu Sans"
        font.pointSize: 9
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

        Widgets.LargeText { text: "Graphics Mode*" }
        Widgets.LargeText { text: "Resolution*" }
        Widgets.LargeText { text: "Texture Size" }
        Widgets.LargeText { text: "Vertical Sync*" }
        Widgets.LargeText { text: "FSAA*" }
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
            options: ["Windowed", "Fullscreen"];
            value: config.getValue("fullscreen") ? 1 : 0;
            onValueChanged: config.setValue("fullscreen", (value == 1))
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: ["1024 x 768", "1920 x 1080"]
            value: options.indexOf(config.getValue("resolution"))
            onValueChanged: config.setValue("resolution", options[value])
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: ["128", "256", "512", "1024", "2048"]
            value: options.indexOf(config.getValue("textureSize"))
            onValueChanged: config.setValue("textureSize", options[value])
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: ["Off", "On"]
            value: config.getValue("vsync") ? 1 : 0;
            onValueChanged: config.setValue("vsync", (value == 1))
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: ["Off", "2X", "4X", "8X"]
            value: {
                var tmp =  config.getValue("fsaa");
                (tmp == 0 ? 0 : options.indexOf(tmp+"X"))
            }
            onValueChanged: config.setValue("fsaa", (value == 0 ? 0 : options[value].substr(0, options[value].length-1)))
        }
    }
}
