import QtQuick 1.0
import "../widgets" as Widgets
import "../functions.js" as Support

Item {
    id: hostGameScreen
    width: 580
    height: 450

    // Position in center
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property string     playername  :       "Player"
    property string     map         :       "Rush-T1"
    property int        players     :       4
    property int        techlevel   :       1
    property bool       fixedTeams  :       false

    property bool       isHosting   :       false

    property variant    subScreen

    function createMenu(name)
    {
        try {
            var myComponent = Qt.createComponent(Support.hostGameList[name][0]);
        }
        catch(e) { console.log("Failed to create hostgame subwidget: " + name); return; }

        if (myComponent == null || myComponent.status == Component.Error)
        {
            console.log(myComponent.errorString());
            return;
        }

        rightSideText.text = Support.hostGameList[name][1]
        hostGameScreen.subScreen = myComponent.createObject(rightBox)
    }

    // Left sideText
    Widgets.SideText {
        id: leftSideText
        text: "Options"
        width: 329
        y: leftBox.height - 31 // 31 = text Height
        x: 2
    }

    // Left blue box
    Widgets.BlueBox {
        id: leftBlueBox
        width: leftBox.width
        height: leftBox.height
    }
    Item {
        id: leftBox
        width: 280
        height: 331

        Widgets.ImageButton {
            id: backButton
            defaultSource: "image://imagemap/icon back"
            hoverSource: "image://imagemap/icon back hi"
            x: 6; y: 5
            onClicked: {
                if (!hostGameScreen.isHosting) {
                    hostGameScreen.destroy();
                    window.loadMenu = window.backMenu;
                    createScreen(window.backScreen);
                } else {
                    hostGameScreen.subScreen.destroy();
                    mapButton.state = ""
                    passwordButton.state = ""
                    hostGameButton.state = ""
                    hostGameButton.opacity = 1
                    hostGameScreen.isHosting = false;
                    backButton.state = ""
                    chatBox.clear()
                }
            }
        }

        Widgets.ImageButton {
            id: limitsButton
            defaultSource: "image://imagemap/icon multiopts"
            hoverSource: "image://imagemap/icon multiopts hi"
            x: 6; y: 43
            onClicked: {
                hostGameScreen.destroy();
                window.loadMenu = window.backMenu;
                createScreen(window.backScreen);
            }
        }

        Widgets.ImageButton {
            id: hostGameButton
            defaultSource: "image://imagemap/icon start game"
            hoverSource: "image://imagemap/icon start game hi"
            x: 6; y: 73
            onClicked: {
                mapButton.state = "off"
                passwordButton.state = "off"
                hostGameButton.state = "off"
                hostGameButton.opacity = 0
                hostGameScreen.isHosting = true
                createMenu("players");
                chatBox.clear()
                chatBox.addSystemMessage("You'r game is not listed. This is a dummy, haha!");
            }
        }

         Column {
            spacing: 4
            width: 226
            x: 50
            y: 2
            Widgets.SingleLineEdit {
                id: playername
                text: hostGameScreen.playername
                maximumLength: 14

                onAccepted: {
                    if (hostGameScreen.playername != text) {
                        chatBox.addLine(hostGameScreen.playername + " -> " + text);
                        hostGameScreen.playername = text
                    }
                }

                Widgets.ImageButton {
                    width: 25
                    y: 3
                    anchors.right: parent.right
                    defaultSource: "image://imagemap/icon flag"
                    hoverSource: "image://imagemap/icon flag hi"
                    activeSource: "image://imagemap/icon flag hi"
                    defaultSourceWidth: 22
                    defaultSourceHeight: 22
                    hoverSourceWidth: 22
                    hoverSourceHeight: 22
                    activeSourceWidth: 22
                    activeSourceHeight: 22
                }
            }
            Widgets.SingleLineEdit {
                text: "One-Player Skirmish"
            }
            Widgets.SingleLineEdit {
                id: map
                text: hostGameScreen.map
                readOnly: true

                Widgets.ImageButton {
                    id: mapButton
                    width: 25
                    y: 3
                    anchors.right: parent.right
                    defaultSource: "image://imagemap/icon select map"
                    hoverSource: "image://imagemap/icon select map hi"
                    activeSource: "image://imagemap/icon select map hi"
                    defaultSourceWidth: 22
                    defaultSourceHeight: 22
                    hoverSourceWidth: 22
                    hoverSourceHeight: 22
                    activeSourceWidth: 22
                    activeSourceHeight: 22

                    onClicked: {
                        mapButton.state = "activeOff";
                        createMenu("mapSelect");
                    }
                }
            }
            Widgets.SingleLineEdit {
                text: "Enter password here"
                Widgets.ImageButton {
                    id: passwordButton
                    width: 25
                    y: 3
                    anchors.right: parent.right
                    defaultSource: "image://imagemap/icon lock off"
                    hoverSource: "image://imagemap/icon lock on"
                    activeSource: "image://imagemap/icon lock on"
                    defaultSourceWidth: 22
                    defaultSourceHeight: 22
                    hoverSourceWidth: 22
                    hoverSourceHeight: 22
                    activeSourceWidth: 22
                    activeSourceHeight: 22

                    onClicked: {
                        defaultSource: "image://imagemap/icon lock on"
                        hoverSource: "image://imagemap/icon lock of"
                        activeSource: "image://imagemap/icon lock off"
                        passwordButton.state = ""
                    }
                }
            }
            Widgets.SingleLineEdit {
                text: "Scavengers"; readOnly: true
                Widgets.ImageSelect {
                    id: scavs
                    x: 105
                    y: 3
                    spacing: 36
                    image1Source: "image://imagemap/SCAVENGERS ON"
                    image1Hover: "image://imagemap/SCAVENGERS ON HI"
                    image1Active: "image://imagemap/QUESTION"
                    image2Source: "image://imagemap/SCAVENGERS OFF"
                    image2Hover: "image://imagemap/SCAVENGERS OFF HI"
                    image2Active: "image://imagemap/QUESTION"
                }
            }
            Widgets.SingleLineEdit {
                text: "Fog"; readOnly: true
                Widgets.ImageSelect {
                    id: fog
                    x: 105
                    y: 3
                    spacing: 36
                    image1Source: "image://imagemap/button eye"
                    image1Hover: "image://imagemap/button eye hi"
                    image1Active: "image://imagemap/button active"
                    image2Source: "image://imagemap/button fog on"
                    image2Hover: "image://imagemap/button fog on hi"
                    image2Active: "image://imagemap/button active"
                }
            }
            Widgets.SingleLineEdit {
                text: "Alliances"; readOnly: true
                Widgets.ImageSelect {
                    id: alliances
                    x: 105
                    y: 3
                    spacing: 36
                    image1Source: "image://imagemap/button ffa"
                    image1Hover: "image://imagemap/button ffa hi"
                    image1Active: "image://imagemap/button active"
                    image2Source: "image://imagemap/button alliances"
                    image2Hover: "image://imagemap/button alliances hi"
                    image2Active: "image://imagemap/button active"
                    image3Source: "image://imagemap/button fixed teams"
                    image3Hover: "image://imagemap/button fixed teams hi"
                    image3Active: "image://imagemap/button active"

                    onClicked: {
                        if (alliances.state == 3) {
                            hostGameScreen.fixedTeams = true
                        }
                        else {
                            hostGameScreen.fixedTeams = false
                        }
                    }
                }
            }
            Widgets.SingleLineEdit {
                text: "Power"; readOnly: true
                Widgets.ImageSelect {
                    id: power
                    x: 105
                    y: 3
                    spacing: 36
                    image1Source: "image://imagemap/button low power"
                    image1Hover: "image://imagemap/button low power hi"
                    image1Active: "image://imagemap/button active"
                    image2Source: "image://imagemap/button medium power"
                    image2Hover: "image://imagemap/button medium power hi"
                    image2Active: "image://imagemap/button active"
                    image3Source: "image://imagemap/button high power"
                    image3Hover: "image://imagemap/button high power hi"
                    image3Active: "image://imagemap/button active"
                }
            }
            Widgets.SingleLineEdit {
                text: "Base"; readOnly: true
                Widgets.ImageSelect {
                    id: base
                    x: 105
                    y: 3
                    spacing: 36
                    image1Source: "image://imagemap/button no bases"
                    image1Hover: "image://imagemap/button no bases hi"
                    image1Active: "image://imagemap/button active"
                    image2Source: "image://imagemap/button medium bases"
                    image2Hover: "image://imagemap/button medium bases hi"
                    image2Active: "image://imagemap/button active"
                    image3Source: "image://imagemap/button full bases"
                    image3Hover: "image://imagemap/button full bases hi"
                    image3Active: "image://imagemap/button active"
                }
            }
            Widgets.SingleLineEdit {
                text: "Map Preview"; readOnly: true
                Widgets.ImageButton {
                    id: fogg_show
                    x: 141
                    y: 3
                    defaultSource: "image://imagemap/button eye"
                    hoverSource: "image://imagemap/button eye hi"
                    activeSource: "image://imagemap/button active"
                }
            }
        }
    }

    // Right blue Box
    Widgets.BlueBox {
        id: rightBlueBox
        width: rightBox.width
        height: rightBox.height
        anchors.left:  leftBlueBox.right
        anchors.leftMargin: 40
    }
    Item {
        id: rightBox
        width: 260
        height: 331
        anchors.left:  rightBlueBox.left
    }


    // Right sideText
    Widgets.SideText {
        id: rightSideText
        text: " "
        width: rightBox.height
        y: rightBox.height - 31 // 31 = text Height
        x: hostGameScreen.width - rightBox.width + 3
    }

    // Bottom blue Box
    Widgets.BlueBox {
        id: bottomBlueBox
        width: bottomBox.width
        height: bottomBox.height
        anchors.top:  leftBlueBox.bottom
        anchors.topMargin: 8
    }

    // Bottom sideText
    Widgets.SideText {
        id: bottomSideText
        text: "Chat"
        width: bottomBox.height
        y: 430 // This should be calculated.
        x: 2
    }

    Item {
        id: bottomBox
        width: parent.width
        height: 120
        anchors.top:  bottomBlueBox.top

        Widgets.Chatbox {
            id: chatBox
            textColor: "white"
            onNewText: {
                chatBox.addLine(playername.text + ": " + chatBox.inputText)
                chatBox.inputText = ""
            }
        }
    }
}
