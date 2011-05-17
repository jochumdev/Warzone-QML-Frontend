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

    Widgets.MenuTextButton { text: "Reverse Rotation"; width: parent.width; bwidth: 248; y: 40; }
    Widgets.MenuTextButton { text: "Trap Cursor"; width: parent.width; bwidth: 248; y: 80; }
    Widgets.MenuTextButton { text: "Switch Mouse Buttons"; width: parent.width; bwidth: 248; y: 120; }
    Widgets.MenuTextButton { text: "Rotate Screen"; width: parent.width; bwidth: 248; y: 160; }
}
