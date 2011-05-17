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

    Widgets.MenuTextButton { text: "Voice Volume"; width: parent.width; bwidth: 248; y: 40; }
    Widgets.MenuTextButton { text: "FX Volume"; width: parent.width; bwidth: 248; y: 80; }
    Widgets.MenuTextButton { text: "Music Volume"; width: parent.width; bwidth: 248; y: 120; }
}
