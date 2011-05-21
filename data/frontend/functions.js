.pragma library

// This library should be replaced by C++ ingame stuff.

var menuList = {
    "mainMenu"              :       ["menu/main.qml", "Main Menu"],
    "singlePlayerMenu"      :       ["menu/singlePlayer.qml", "Single Player"],
    "optionsMenu"           :       ["menu/options.qml", "Options"],
    "tutorialsMenu"         :       ["menu/tutorials.qml", "Tutorials"],

    "gameOptionsMenu"       :       ["menu/gameOptions.qml", "Game Options"],
    "graphicsOptionsMenu"   :       ["menu/graphicsOptions.qml", "Graphics Options"],
    "videoOptionsMenu"      :       ["menu/videoOptions.qml", "Video Options"],
    "audioOptionsMenu"      :       ["menu/audioOptions.qml", "Audio Options"],
    "mouseOptionsMenu"      :       ["menu/mouseOptions.qml", "Mouse Options"],
    "keyMappingMenu"        :       ["menu/keyMappings.qml", "Key Mapping"]
}


// Full Screen templates
// Widget(sets) will be loaded into this templates.
var screenList = {
    "menuScreen"            :       ["screens/menuScreen.qml"],
    "hostGameScreen"        :       ["screens/hostGameScreen.qml"],
    "limitsScreen"          :       []
}

var hostGameList = {
    "mapSelect"             :       ["hostGame/mapSelect.qml", "Select Map"],
    "players"               :       ["hostGame/players.qml", "Players"]
}

var backgrounds = ["Background 0",
                   "Background 1",
                   "Background 2",
                   "Background 3",
                   "Background 4",
                   "Background 5"]

var maps = {
     "Startup"      : {"players": 2, "techlevels": [1,2,3]},
     "UrbanChaos"   : {"players": 2, "techlevels": [1,2,3]},
     "HighGround"   : {"players": 2, "techlevels": [1,2,3]},
     "Roughness"    : {"players": 2, "techlevels": [1,2,3]},
     "Vision"       : {"players": 2, "techlevels": [1,2,3]},

     "Rush"         : {"players": 4, "techlevels": [1,2,3]},
     "Rush2"        : {"players": 4, "techlevels": [1,2,3]},
     "UrbanDuel"    : {"players": 4, "techlevels": [1,2,3]},
     "Mountain"     : {"players": 4, "techlevels": [1,2,3]},
     "Valley"       : {"players": 4, "techlevels": [1,2,3]},
     "FishNets"     : {"players": 4, "techlevels": [1,2,3]},
     "GreatRift"    : {"players": 4, "techlevels": [1,2,3]},
     "RollingHills" : {"players": 4, "techlevels": [1,2,3]},
     "Basingstoke"  : {"players": 4, "techlevels": [1,2,3]},
     "LittleEgypt"  : {"players": 4, "techlevels": [1,2,3]},
     "cockpit"      : {"players": 4, "techlevels": [1,2,3]},
     "Urban-Chaos"  : {"players": 4, "techlevels": [1,2,3]},
     "Pyramidal"    : {"players": 4, "techlevels": [1,2,3]},
     "Annhiliators_Map"     : {"players": 4, "techlevels": [1,2,3]},

     "Clover"       : {"players": 8, "techlevels": [1,2,3]},
     "MizaMaze"     : {"players": 8, "techlevels": [1,2,3]},
     "Manhattan"    : {"players": 8, "techlevels": [1,2,3]},
     "Bananas"      : {"players": 8, "techlevels": [1,2,3]},
     "Ziggurat"     : {"players": 8, "techlevels": [1,2,3]},
     "Concrete"     : {"players": 8, "techlevels": [1,2,3]},
     "ThePit"       : {"players": 8, "techlevels": [1,2,3]},
     "HideNSneak"   : {"players": 8, "techlevels": [1,2,3]},
     "YingYang"     : {"players": 8, "techlevels": [1,2,3]},
     "SandCastles"  : {"players": 8, "techlevels": [1,2,3]},
     "BeggarsKanyon" : {"players": 8, "techlevels": [1,2,3]},
     "Gridlock"     : {"players": 8, "techlevels": [1,2,3]},
     "cockate"      : {"players": 8, "techlevels": [1,2,3]},
     "SquaredV7"    : {"players": 8, "techlevels": [1,2,3]},
}

function getRandBackground()
{
    return backgrounds[(Math.floor(Math.random() * backgrounds.length))];
}

