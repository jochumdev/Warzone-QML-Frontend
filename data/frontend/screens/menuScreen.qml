import QtQuick 1.0
import "../widgets" as Widgets
import "../functions.js" as Support

Item {
    id: menuScreen
    width: 480
    height: 460 // topBox + spacer + mainBox

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    Component.onCompleted: createMenu(window.loadMenu)

    function createMenu(name)
    {
        try {
            var myComponent = Qt.createComponent(Support.menuList[name][0]);
        }
        catch(e) { console.log("Failed to load menu: " + name); return; }

        if (myComponent == null || myComponent.status == Component.Error)
        {
            console.log(myComponent.errorString());
            return;
        }

        myComponent.createObject(menuHolder)
        sideText.text = Support.menuList[name][1]
    }

    function destroyScreen()
    {
        menuScreen.destroy();
    }

    // Top blue box
    Widgets.BlueBox {
        width: parent.width
        height: 150
    }

    // Top box
    Item {
        id: topBox

        width: parent.width
        height: 150

        // Logo
        Image {
            source: "image://imagemap/FE LOGO:height"
            sourceSize.width: 10
            sourceSize.height: 115
            opacity: 1
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
        }
    }

    // Sidetext
    Widgets.SideText {
        id: sideText
        text: "Main menu"
        width: 300
        y: 437
        x: -10
    }

    // Main blue box
    Widgets.BlueBox {
        id: mainBox
        width: parent.width
        height: 300
        anchors.top:  topBox.bottom
        anchors.topMargin: 10
    }

    Item {
        id: menuHolder
        width: parent.width
        height: 300
        anchors.top:  topBox.bottom
        anchors.topMargin: 10
    }
}
