import QtQuick 1.0
import "../../widgets" as Widgets

Item {
    id: keyMappingsMenu

    width: parent.width
    height: parent.height

    Widgets.ImageButton {
        defaultSource: "image://imagemap/icon back"
        hoverSource: "image://imagemap/icon back hi"
        x: 5; y: 5
        onClicked: {
            keyMappingsMenu.destroy();
            createMenu("optionsMenu");
        }
    }

    Widgets.MenuTextButton { text: "Holy-..."; width: parent.width; bwidth: 248; y: 40; }
}
