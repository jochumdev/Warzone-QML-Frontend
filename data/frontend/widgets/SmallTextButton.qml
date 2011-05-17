import QtQuick 1.0

Rectangle {
    id: container

    signal clicked

    property alias text                : _text.text
    property bool  active              : false

    color: "#000161"
    border.color: "#0015f0"
    border.width: 1
    width: 19; height: 19

    Text {
        id: _text
        x: 3
        y: 3
        color: "grey"
        smooth: true
        font.family: "DejaVu Sans"
        font.pointSize: 9
    }

    MouseArea {
        id: ma
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onEntered: { parent.state = "hover" }
        onExited: { if (!parent.active) { parent.state = "default"; } }
        onClicked: {
            parent.clicked();
            parent.state = "active"
            parent.active = true;
        }

    }

    states: [
        State {
            name: "default"
            PropertyChanges { target: _text; color: "grey" }
        },
        State {
            name: "hover"
            PropertyChanges { target: _text; color: "white" }
        },
        State {
            name: "active"
            PropertyChanges { target: _text; color: "white" }
        }
    ]
}