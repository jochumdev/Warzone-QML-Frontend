import QtQuick 1.0
import "../widgets" as Widgets

Rectangle {
    id: container
    width: parent.width

    signal clicked

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

    property alias image1State  : image1.state
    property alias image2State  : image2.state
    property alias image3State  : image3.state


    Widgets.ImageButton {
        id: image1
        onClicked: {
            parent.state = "1";
            parent.clicked();
        }
    }
    Widgets.ImageButton {
        id: image2
        anchors.left:  image1.right
        anchors.leftMargin: parent.spacing
        onClicked: {
            parent.state = "2";
            parent.clicked();
        }
    }
    Widgets.ImageButton {
        id: image3
        anchors.left:  image2.right
        anchors.leftMargin: parent.spacing
        onClicked: {
            parent.state = "3";
            parent.clicked();
        }
    }

    states: [
            State {
                    name: "1"
                    PropertyChanges { target: image1; state: "active" }
                    PropertyChanges { target: image2; state: "" }
                    PropertyChanges { target: image3; state: "" }
            },
            State {
                    name: "2"
                    PropertyChanges { target: image1; state: "" }
                    PropertyChanges { target: image2; state: "active" }
                    PropertyChanges { target: image3; state: "" }
            },
            State {
                    name: "3"
                    PropertyChanges { target: image1; state: "" }
                    PropertyChanges { target: image2; state: "" }
                    PropertyChanges { target: image3; state: "active" }
            }
   ]
}