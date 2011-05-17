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

    Widgets.MenuTextButton { text: "Difficulty"; width: parent.width; bwidth: 248; y: 40; }
    Widgets.MenuTextButton { text: "Scroll Speed"; width: parent.width; bwidth: 248; y: 80; }
    Widgets.MenuTextButton { text: "Unit Colour"; width: parent.width; bwidth: 248; y: 120; }
    Widgets.MenuTextButton { text: "Language"; width: parent.width; bwidth: 248; y: 160; }
    Widgets.MenuTextButton { text: "Radar"; width: parent.width; bwidth: 248; y: 200; }
}
