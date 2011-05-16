import QtQuick 1.0
import "../widgets" as Widgets

Rectangle {
    id: container
    width: parent.width

    signal changed

    property int   active       : 0

    property int   spacing      : 40
    property alias image1Source : image1.defaultSource
    property alias image2Source : image2.defaultSource
    property alias image3Source : image3.defaultSource
    property alias image1Hover  : image1.hoverSource
    property alias image2Hover  : image2.hoverSource
    property alias image3Hover  : image3.hoverSource
    property alias image1Active : image1.activeSource
    property alias image2Active : image2.activeSource
    property alias image3Active : image3.activeSource

    /** Disable a single button **/
    property alias image1Off    : image1.off
    property alias image2Off    : image2.off
    property alias image3Off    : image3.off


    Widgets.ImageButton {
        id: image1
        //sourceSize.width: undefined
        //sourceSize.height: undefined
        selectButton: true
        onClicked: {
            if (parent.active != 1) {
                parent.active = 1
                parent.changed()
                image2.active = false
                image2.state = "default"
                image3.active = false
                image3.state = "default"
            }
        }
    }
    Widgets.ImageButton {
        id: image2
        //sourceSize.width: undefined
        //sourceSize.height: undefined
        selectButton: true
        anchors.left:  image1.right
        anchors.leftMargin: parent.spacing
        onClicked: {
            if (parent.active != 2) {
                parent.active = 2
                parent.changed()
                image1.active = false
                image1.state = "default"
                image3.active = false
                image3.state = "default"
            }
        }
    }
    Widgets.ImageButton {
        id: image3
        //sourceSize.width: undefined
        //sourceSize.height: undefined
        selectButton: true
        anchors.left:  image2.right
        anchors.leftMargin: parent.spacing
        onClicked: {
            if (parent.active != 3) {
                parent.active = 3
                parent.changed()
                image1.active = false
                image1.state = "default"
                image2.active = false
                image2.state = "default"
            }
        }
    }
}