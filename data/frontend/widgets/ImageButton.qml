import QtQuick 1.0

Rectangle {
    id: container

    signal clicked

    property alias defaultSource       : image.source
    property alias defaultSourceWidth  : image.sourceSize.width
    property alias defaultSourceHeight : image.sourceSize.height
    property alias hoverSource         : hover.source
    property alias hoverSourceWidth    : hover.sourceSize.width
    property alias hoverSourceHeight   : hover.sourceSize.height
    property alias activeSource        : active.source
    property alias activeSourceWidth   : active.sourceSize.width
    property alias activeSourceHeight  : active.sourceSize.height
    property bool  overlay             : true
    property bool  off                 : false

    /** Used to control the state of a seclect imagebutton */
    property bool  selectButton        : false
    property bool  active              : false

    Component.onCompleted: {
        image.source = defaultSource
        if (off) { ma.enabled = false; image.opacity = 0.6 }
    }

    Image {
        id: image
        opacity: 1
    }

    Image {
        id: hover
        opacity: 0
    }

    Image {
        id: active
        opacity: 0
    }

    MouseArea {
        id: ma
        anchors.fill: image
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onEntered: {
            if (parent.overlay) {
                parent.state = "hoverOverlay"
            } else {
                parent.state = "hover"
            }
        }
        onExited: {
            if (!parent.selectButton || !parent.active)
            {
                if (parent.overlay) {
                    parent.state = "defaultOverlay"
                } else {
                    parent.state = "default"
                }
            }

        }
        onClicked: {
            container.clicked();

            if (parent.overlay) {
                parent.state = "activeOverlay"
            } else {
                parent.state = "active"
            }

            if (parent.selectButton) {
                parent.active = true
            }
        }
    }

    states: [
            State {
                    name: "defaultOverlay"
                    PropertyChanges { target: image; opacity: 1 }
                    PropertyChanges { target: container; active: false }
            },
            State {
                    name: "hoverOverlay"
                    PropertyChanges { target: hover; opacity: 1 }
            },
            State {
                    name: "activeOverlay"
                    PropertyChanges { target: hover; opacity: 1 }
                    PropertyChanges { target: active; opacity: 1 }
            },
            State {
                    name: "default"
                    PropertyChanges { target: image; opacity: 1 }
                    PropertyChanges { target: hover; opacity: 0 }
                    PropertyChanges { target: active; opacity: 0 }
                    PropertyChanges { target: container; active: false }
            },
            State {
                    name: "hover"
                    PropertyChanges { target: image; opacity: 0 }
                    PropertyChanges { target: hover; opacity: 1 }
                    PropertyChanges { target: active; opacity: 0 }
            },
            State {
                    name: "active"
                    PropertyChanges { target: image; opacity: 0 }
                    PropertyChanges { target: hover; opacity: 0 }
                    PropertyChanges { target: active; opacity: 1 }
            }
    ]
}
