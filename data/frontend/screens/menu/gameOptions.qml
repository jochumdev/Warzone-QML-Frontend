import QtQuick 1.0
import "../../widgets" as Widgets

Item {
    id: gameOptionsMenu

    width: parent.width
    height: parent.height

    Widgets.ImageButton {
        defaultSource: "image://imagemap/icon back"
        hoverSource: "image://imagemap/icon back hi"
        x: 5; y: 5
        onClicked: {
            gameOptionsMenu.destroy();
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

        Widgets.LargeText { text: "Difficulty" }
        Widgets.LargeText { text: "Scroll Speed" }
        Widgets.LargeText { text: "Unit Colour" }
        Widgets.LargeText { text: "Language" }
        Widgets.LargeText { text: "Radar" }
    }

    // Options
    Column {
        width: 165
        anchors.top: parent.top
        anchors.topMargin: 56
        anchors.left: labels.right

        spacing: 15
        Widgets.ClickSelect {
            width: parent.width
            options: ["Easy", "Normal", "Hard", "Tough", "Killer"]
            value: config.getValue("difficulty")
            onValueChanged: config.setValue("difficulty", value)
        }
        Widgets.Slider {
            width: parent.width
            maximum: 16
            value: config.getValue("scroll") / 100
            onValueChanged: config.setValue("scroll", value * 100)
        }
        Widgets.ImageSelectV2 {
            id: color
            width: parent.width; height: 25
            model: ListModel {
                ListElement {
                    value: "0"
                    defaultSource2: "image://imagemap/icon player0"
                    hoverSource2: "image://imagemap/icon player0 hi"
                    activeSource2: "image://imagemap/icon player0 hi"
                }
                ListElement {
                    value: "4"
                    defaultSource2: "image://imagemap/icon player4"
                    hoverSource2: "image://imagemap/icon player4 hi"
                    activeSource2: "image://imagemap/icon player4 hi"
                }
                ListElement {
                    value: "5"
                    defaultSource2: "image://imagemap/icon player5"
                    hoverSource2: "image://imagemap/icon player5 hi"
                    activeSource2: "image://imagemap/icon player5 hi"
                }
                ListElement {
                    value: "6"
                    defaultSource2: "image://imagemap/icon player6"
                    hoverSource2: "image://imagemap/icon player6 hi"
                    activeSource2: "image://imagemap/icon player6 hi"
                }
                ListElement {
                    value: "7"
                    defaultSource2: "image://imagemap/icon player7"
                    hoverSource2: "image://imagemap/icon player7 hi"
                    activeSource2: "image://imagemap/icon player7 hi"
                }
            }

            value: config.getValue("colour")
            onValueChanged: config.setValue("colour", value)
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: ["System locale", "German", "English"]
            value: {
                var index = options.indexOf(config.getValue("language"));
                (index == -1 ? 0 : index)
            }
            onValueChanged: config.setValue("language", options[value])
        }
        Widgets.ClickSelect {
            width: parent.width;
            options: ["Fixed", "Rotating"]
            value: config.getValue("rotateRadar") ? 1 : 0;
            onValueChanged: config.setValue("rotateRadar", (value == 1))
        }
    }
}
