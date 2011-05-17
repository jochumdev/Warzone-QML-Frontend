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

    Widgets.MenuTextButton { text: "Graphics Mode"; width: parent.width; bwidth: 248; y: 40; }
    Widgets.MenuTextButton { text: "Resolution"; width: parent.width; bwidth: 248; y: 80; }
    Widgets.MenuTextButton { text: "Texture Size"; width: parent.width; bwidth: 248; y: 120; }
    Widgets.MenuTextButton { text: "Vertical Sync"; width: parent.width; bwidth: 248; y: 160; }
    Widgets.MenuTextButton { text: "FSAA"; width: parent.width; bwidth: 248; y: 200; }
}
