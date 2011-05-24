import QtQuick 1.0

Text {
    id: container

    signal clicked

    property variant options:   []
    property variant currentIndex: 0

    text: container.options[currentIndex]

    color: "#a0a0ff"
    font.weight: Font.DemiBold
    font.family: "DejaVu Sans"
    font.pixelSize: 21
    smooth: true


    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        hoverEnabled: true
        onEntered: { parent.state = "hover" }
        onExited: { parent.state = "" }

        onClicked: {
            if (container.options.length > container.currentIndex+1)
            {
                container.currentIndex += 1
            }
            else
            {
                container.currentIndex = 0
            }

            container.clicked()
        }
    }

    states: [
        State {
                name: "hover"
                PropertyChanges { target: container; color: "#ffffff" }
        }
    ]
}