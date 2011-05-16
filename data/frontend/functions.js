.pragma library

// This library should be replaced by C++ ingame stuff.

var menuList = {
    "mainMenu"              :       ["../menus/mainMenu.qml", "Main Menu"],
    "singlePlayerMenu"      :       ["../menus/singlePlayerMenu.qml", "Single Player"],
    "optionsMenu"           :       ["../menus/optionsMenu.qml", "Options"],
    "tutorialsMenu"         :       ["../menus/tutorialsMenu.qml", "Tutorials"],

    "gameOptionsMenu"       :       ["../menus/gameOptions.qml", "Game Options"],
    "graphicsOptionsMenu"   :       ["../menus/graphicsOptions.qml", "Graphics Options"],
    "videoOptionsMenu"      :       ["../menus/videoOptions.qml", "Video Options"],
    "audioOptionsMenu"      :       ["../menus/audioOptions.qml", "Audio Options"],
    "mouseOptionsMenu"      :       ["../menus/mouseOptions.qml", "Mouse Options"],
    "keyMappingMenu"        :       ["../menus/keyMappings.qml", "Key Mapping"]
}


// Full Screen templates
// Widget(sets) will be loaded into this templates.
var screenList = {
    "menuScreen"            :       ["screens/menuScreen.qml"],
    "hostGameScreen"        :       ["screens/hostGameScreen.qml"],
    "limitsScreen"          :       []
}


var backgrounds = new Array("Background 0",
                            "Background 1",
                            "Background 2",
                            "Background 3",
                            "Background 4",
                            "Background 5")

function getRandBackground()
{
    return backgrounds[(Math.floor(Math.random() * backgrounds.length))];
}

