import QtQuick 1.0
import "../../widgets" as Widgets

Item {
    id: container
    anchors.fill: parent

    ListModel {
        id: playersModel
    }

    Component.onCompleted: {
        playersModel.append({isAI: false, team: "TEAM0", playerColor: "player0", name: hostGameScreen.playername, isReady: false,
                            statsPlayed: 0, statsWins: 0, statsLosses: 0, statsTotalKills: 0, statsTotalScore: 0});

        for(var i=1;i<hostGameScreen.players;i++) {
            playersModel.append({isAI: true, team: "TEAM"+i, playerColor: "player"+i, name: "Nexus", isReady: true,
                                 statsPlayed: 0, statsWins: 0, statsLosses: 0, statsTotalKills: 0, statsTotalScore: 0});
        }
    }

    Component {
        id: playersDelegate

        Rectangle {
            width: hostGameScreen.fixedTeams ? 248 : 217
            height: 38

            color: "#000161"
            border.color: "#0015f0"
            border.width: 1

            anchors.right: parent.right

            Rectangle {
                id: teamselector
                width: 31; height: parent.height

                color: "#000161"
                border.color: "#0015f0"
                border.width: 1

                Widgets.ImageButton {
                    x: 3
                    y: 9

                    defaultSource: "image://imagemap/" + team
                    defaultSourceWidth: 25
                    defaultSourceHeight: 21
                    hoverSource: "image://imagemap/" + team + " HI"
                    hoverSourceWidth: 25
                    hoverSourceHeight: 21
                    activeSource: "image://imagemap/" + team + " HI"
                    activeSourceWidth: 25
                    activeSourceHeight: 21
                }
            }

            Rectangle {
                id: colorflag
                width: 33; height: parent.height

                anchors.left: hostGameScreen.fixedTeams ? teamselector.right : parent.left

                color: "#000161"
                border.color: "#0015f0"
                border.width: 1

                Widgets.ImageButton {
                    x: 7
                    y: 9

                    defaultSource: "image://imagemap/icon " + playerColor
                    defaultSourceWidth: 22
                    defaultSourceHeight: 19
                    hoverSource: "image://imagemap/icon " + playerColor + " hi"
                    hoverSourceWidth: 22
                    hoverSourceHeight: 19
                    activeSource: "image://imagemap/icon " + playerColor + " hi"
                    activeSourceWidth: 22
                    activeSourceHeight: 19
                }
            }

            Item  {
                id: rank
                width: 28; height: parent.height

                anchors.left: colorflag.right

                Image {
                    id: topstar

                    anchors.top: parent.top
                    anchors.topMargin: 4
                    anchors.left: parent.left
                    anchors.leftMargin: 4

                    source: {
                        if (statsTotalKills >600)
                        {
                            "image://imagemap/star gold"
                        }
                        else if (statsTotalKills >300)
                        {
                            "image://imagemap/star silver"
                        }
                        else if (statsTotalKills >150)
                        {
                            "image://imagemap/star bronze"
                        }
                        else
                        {
                            "image://imagemap/empty"
                        }
                    }
                    sourceSize.width: 8
                    sourceSize.height: 8

                    opacity: isAI ? 0 : 1
                }

                Image {
                    id: middlestar

                    anchors.top: topstar.bottom
                    anchors.topMargin: 2
                    anchors.left: parent.left
                    anchors.leftMargin: 4

                    source: {
                        if (statsPlayed >600)
                        {
                            "image://imagemap/star gold"
                        }
                        else if (statsPlayed >300)
                        {
                            "image://imagemap/star silver"
                        }
                        else if (statsPlayed >150)
                        {
                            "image://imagemap/star bronze"
                        }
                        else
                        {
                            "image://imagemap/empty"
                        }
                    }
                    sourceSize.width: 8
                    sourceSize.height: 8

                    opacity: isAI ? 0 : 1
                }

                Image {
                    id: bottomstar

                    anchors.top: middlestar.bottom
                    anchors.topMargin: 2
                    anchors.left: parent.left
                    anchors.leftMargin: 4

                    source: {
                        if (statsWins >600)
                        {
                            "image://imagemap/star gold"
                        }
                        else if (statsWins >300)
                        {
                            "image://imagemap/star silver"
                        }
                        else if (statsWins >150)
                        {
                            "image://imagemap/star bronze"
                        }
                        else
                        {
                            "image://imagemap/empty"
                        }
                    }
                    sourceSize.width: 8
                    sourceSize.height: 8

                    opacity: isAI ? 0 : 1
                }



                Image {
                    anchors.left: topstar.right
                    anchors.leftMargin: 1
                    anchors.top: parent.top
                    anchors.topMargin: 8

                    source: {
                        if (statsPlayed < 5) {
                            "image://imagemap/medal dummy"
                        }
                        else if (statsWins >= 24 && (statsWins > (8 * statsLosses)))
                        {
                            "image://imagemap/medal gold"
                        }
                        else if (statsWins >= 12 && (statsWins > (4 * statsLosses)))
                        {
                            "image://imagemap/medal silver"
                        }
                        else if (statsWins >= 6 && (statsWins > (2 * statsLosses)))
                        {
                            "image://imagemap/medal bronze"
                        }
                        else
                        {
                            "image://imagemap/empty"
                        }
                    }
                    sourceSize.width: 12
                    sourceSize.height: 50

                    opacity: isAI ? 0 : 1
                }
            }

            Text {
                id: text
                text: name

                anchors.left: rank.right
                anchors.right: checkbox.left
                anchors.top: parent.top
                anchors.topMargin: 12

                color: "#aeaeb7"
                smooth: true
                font.family: "DejaVu Sans"
                font.pointSize: 9
            }

            Rectangle {
                id: checkbox
                width: 43; height: parent.height

                anchors.right: parent.right

                color: "#000161"
                border.color: "#0015f0"
                border.width: 1

                Image {
                    x: 10
                    y: 14
                    source: (isAI ? "image://imagemap/icon ai player" : (isReady ? "image://imagemap/icon checkbox on" : "image://imagemap/icon checkbox off"))
                    sourceSize.width: 22
                    sourceSize.height: 22

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton

                        enabled: !isAI

                        onClicked: playersModel.setProperty(index, "isReady", !isReady)
                    }
                }
            }
        }
    }

    ListView {
        id: view

        anchors.fill: parent
        anchors.leftMargin: 6
        anchors.rightMargin: 6
        anchors.topMargin: 2
        anchors.bottomMargin: 2

        spacing: 3

        model: playersModel
        delegate: playersDelegate
    }
}