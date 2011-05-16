import QtQuick 1.0
import "../widgets" as Widgets

Item {
    id: tutorialMenu

    width: parent.width
    height: parent.height

    Widgets.ImageButton {
        defaultSource: "image://imagemap/icon back"
        hoverSource: "image://imagemap/icon back hi"
        x: 5; y: 5
        onClicked: {
            tutorialMenu.destroy();
            createMenu("mainMenu");
        }
    }

    Widgets.MenuTextButton { text: "Tutorial"; width: parent.width; bwidth: 248; y: 40; }
    Widgets.MenuTextButton { text: "Fast Play"; width: parent.width; bwidth: 248; y: 80; }
}
