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

    Widgets.MenuTextButton { text: "Video Playback"; width: parent.width; bwidth: 248; y: 40; }
    Widgets.MenuTextButton { text: "Scanlines"; width: parent.width; bwidth: 248; y: 80; }
    Widgets.MenuTextButton { text: "Screen Shake"; width: parent.width; bwidth: 248; y: 120; }
    Widgets.MenuTextButton { text: "Fog"; width: parent.width; bwidth: 248; y: 160; }
    Widgets.MenuTextButton { text: "Subtitles"; width: parent.width; bwidth: 248; y: 200; }
    Widgets.MenuTextButton { text: "Shadows"; width: parent.width; bwidth: 248; y: 240; }
}
