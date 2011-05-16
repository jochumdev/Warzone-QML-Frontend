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

    Component.onCompleted: {
        window.loadMenu = "mainMenu"
        createScreen("menuScreen")
    }

    function createScreen(name)
    {
        try {
            var myComponent = Qt.createComponent(Support.screenList[name][0]);
        }
        catch(e) { console.log("Failed to load screen: " + name); return; }

        if (myComponent == null || myComponent.status == Component.Error)
        {
            console.log(myComponent.errorString());
            return;
        }

        myComponent.createObject(window)
    }

    // Show the pumpkin(g)
    function quit()
    {
        var myComponent = Qt.createComponent("quit.qml")
        if (myComponent == null || myComponent.status == Component.Error)
        {
            console.log(myComponent.errorString());
            return;
        }
        myComponent.createObject(window)
    }
}
