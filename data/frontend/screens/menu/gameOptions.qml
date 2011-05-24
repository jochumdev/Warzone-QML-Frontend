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
        Widgets.ClickSelect {width: parent.width; options: ["Normal", "Hard", "Easy"]}
        Widgets.Slider {width: parent.width; value: 0}
        Widgets.ImageSelectV2 {
            id: color
            width: parent.width; height: 25
            model: ListModel {
                ListElement {
                    value: "green"
                    defaultSource2: "image://imagemap/icon player0"
                    hoverSource2: "image://imagemap/icon player0 hi"
                    activeSource2: "image://imagemap/icon player0 hi"
                    state2: "active"
                }
                ListElement {
                    value: "orange"
                    defaultSource2: "image://imagemap/icon player1"
                    hoverSource2: "image://imagemap/icon player1 hi"
                    activeSource2: "image://imagemap/icon player1 hi"
                    state2: ""
                }
                ListElement {
                    value: "grey"
                    defaultSource2: "image://imagemap/icon player2"
                    hoverSource2: "image://imagemap/icon player2 hi"
                    activeSource2: "image://imagemap/icon player2 hi"
                    state2: ""
                }
                ListElement {
                    value: "black"
                    defaultSource2: "image://imagemap/icon player3"
                    hoverSource2: "image://imagemap/icon player3 hi"
                    activeSource2: "image://imagemap/icon player3 hi"
                    state2: ""
                }
                ListElement {
                    value: "red"
                    defaultSource2: "image://imagemap/icon player4"
                    hoverSource2: "image://imagemap/icon player4 hi"
                    activeSource2: "image://imagemap/icon player4 hi"
                    state2: ""
                }
            }
        }
        Widgets.ClickSelect {width: parent.width; options: ["System locale", "German", "English"]}
        Widgets.ClickSelect {width: parent.width; options: ["Rotating", "Fixed"]}
    }
}
