import QtQuick 1.0
import "widgets" as Widgets
import "functions.js" as Support

Image {
    id: window

    width: 1024; height: 768

    source: "image://imagemap/" + Support.getRandBackground()
    fillMode:  Image.Stretch

    property string backScreen
    property string backMenu
    property string loadMenu

    property variant _subScreen

    Component.onCompleted: {
        window.loadMenu = "menu/main.qml"
        createScreen("screens/menuScreen.qml")
    }

    function createScreen(file)
    {
        if (window._subScreen) {
            window._subScreen.destroy();
        }

        try {
            var myComponent = Qt.createComponent(file);
        }
        catch(e) { console.log("Failed to load screen: " + name); return; }

        if (myComponent == null || myComponent.status == Component.Error) {
            console.log(myComponent.errorString());
            return;
        }

        window._subScreen = myComponent.createObject(window)
    }
}
