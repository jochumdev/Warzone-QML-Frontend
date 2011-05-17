import QtQuick 1.0
import "../../widgets" as Widgets

Item {
    id: singlePlayerMenu

    width: parent.width
    height: parent.height

    Widgets.ImageButton {
        defaultSource: "image://imagemap/icon back"
        hoverSource: "image://imagemap/icon back hi"
        x: 5; y: 5
        onClicked: {
            singlePlayerMenu.destroy();
            createMenu("mainMenu");
        }
    }

    Widgets.MenuTextButton { text: "New Campaign"; width: parent.width; bwidth: 248; y: 40; }
    Widgets.MenuTextButton {
        text: "Start Skirmish Game"; width: parent.width; bwidth: 248; y: 80;
        onClicked: {
            destroyScreen();
            window.backScreen = "menuScreen"; window.backMenu = "singlePlayerMenu";
            createScreen("hostGameScreen");
        }
    }
    Widgets.MenuTextButton { text: "Challenges"; width: parent.width; bwidth: 248; y: 120; }
    Widgets.MenuTextButton { text: "Load Game"; width: parent.width; bwidth: 248; y: 160; }
}
