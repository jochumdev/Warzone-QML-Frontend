import QtQuick 1.0
import "../../widgets" as Widgets

Item {
    id: optionsMenu

    width: parent.width
    height: parent.height

    Widgets.ImageButton {
        defaultSource: "image://imagemap/icon back"
        hoverSource: "image://imagemap/icon back hi"
        x: 5; y: 5
        onClicked: {
            optionsMenu.destroy();
            createMenu("mainMenu");
        }
    }

    Widgets.MenuTextButton { text: "Game Options"; width: parent.width; bwidth: 248; y: 40; }
    Widgets.MenuTextButton { text: "Graphics Options"; width: parent.width; bwidth: 248; y: 80; }
    Widgets.MenuTextButton { text: "Video Options"; width: parent.width; bwidth: 248; y: 120; }
    Widgets.MenuTextButton { text: "Audio Options"; width: parent.width; bwidth: 248; y: 160; }
    Widgets.MenuTextButton { text: "Mouse Options"; width: parent.width; bwidth: 248; y: 200; }
    Widgets.MenuTextButton { text: "Key Mappings"; width: parent.width; bwidth: 248; y: 240; }
}
