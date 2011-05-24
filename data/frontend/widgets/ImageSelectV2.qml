import QtQuick 1.0

Item {
    id: container

    signal clicked

    property alias      orientation: view.orientation
    property variant    value      : ""
    property int        spacing    : 1
    property int        active     : 0
    property variant    model

    ListView {
        id: view
        interactive: false

        anchors.fill: parent

        orientation: ListView.Horizontal
        spacing: container.spacing


        Component {
            id: delegate

            Image {
                id: image
                source: defaultSource2

                Image {
                    id: active
                    source: activeSource2

                    opacity: (container.active == index ? 1 : 0)
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                    onClicked: {
                        container.active = index
                        container.value = value
                        container.clicked()
                    }
                }
            }
        }

        model: container.model
        delegate: delegate
        focus: true
    }
}