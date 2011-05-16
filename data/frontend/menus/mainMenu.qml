import QtQuick 1.0
import "../widgets" as Widgets

Item {
    id: mainMenu

    width: parent.width
    height: parent.height

    Widgets.MenuTextButton { text: "Single Player"; width: parent.width; bwidth: 248; y: 40; onClicked: {mainMenu.destroy(), createMenu("singlePlayerMenu")} }
    Widgets.MenuTextButton { text: "Multi Player"; width: parent.width; bwidth: 248; y: 80; }
    Widgets.MenuTextButton { text: "Tutorial"; width: parent.width; bwidth: 248; y: 120; onClicked: {mainMenu.destroy(); createMenu("tutorialsMenu")} }
    Widgets.MenuTextButton { text: "Options"; width: parent.width; bwidth: 248; y: 160; onClicked: {mainMenu.destroy(); createMenu("optionsMenu")} }
    Widgets.MenuTextButton { text: "View Intro"; width: parent.width; bwidth: 248; y: 200; }
    Widgets.MenuTextButton { text: "Quit Game"; width: parent.width; bwidth: 248; y: 240; onClicked: {mainMenu.destroy(); quit();} }
}
