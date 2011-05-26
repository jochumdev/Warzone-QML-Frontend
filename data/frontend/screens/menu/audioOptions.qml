import QtQuick 1.0
import "../../widgets" as Widgets

Item {
    id: audioOptionsMenu

    width: parent.width
    height: parent.height

    Widgets.ImageButton {
        defaultSource: "image://imagemap/icon back"
        hoverSource: "image://imagemap/icon back hi"
        x: 5; y: 5
        onClicked: {
            audioOptionsMenu.destroy();
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

        Widgets.LargeText { text: "Voice Volume" }
        Widgets.LargeText { text: "FX Volume" }
        Widgets.LargeText { text: "Music Volume" }
    }

    // Options
    Column {
        width: 165
        anchors.top: parent.top
        anchors.topMargin: 56
        anchors.left: labels.right

        spacing: 24
        Widgets.Slider {width: parent.width; value: config.getValue("voicevol"); onValueChanged: config.setValue("voicevol", value)}
        Widgets.Slider {width: parent.width; value: config.getValue("fxvol"); onValueChanged: config.setValue("fxvol", value)}
        Widgets.Slider {width: parent.width; value: config.getValue("cdvol"); onValueChanged: config.setValue("cdvol", value)}
    }
}
