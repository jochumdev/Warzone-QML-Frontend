.pragma library

// This library should be replaced by C++ ingame stuff.
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

var backgrounds = ["Background 0",
                   "Background 1",
                   "Background 2",
                   "Background 3",
                   "Background 4",
                   "Background 5"]

function getRandBackground()
{
    return backgrounds[(Math.floor(Math.random() * backgrounds.length))];
}

