import QtQuick 1.0
import "../widgets" as Widgets

Item {
    id: chatbox
    anchors.fill: parent

    property string textColor: "black"
    property int margins: 2
    property alias text: _text.text

    Flickable {
        id: view
        width: parent.width - parent.margins * 2
        height: parent.height - parent.margins * 2
        x: parent.margins; y: parent.margins;
        contentWidth: _text.width
        contentHeight: _text.height
        flickableDirection: Flickable.VerticalFlick

        boundsBehavior: Flickable.StopAtBounds
        clip: true

        TextEdit {
            id: _text
            color: chatbox.textColor

            width: chatbox.width - chatbox.margins * 2
            height: chatbox.height * 5

            wrapMode: Text.WordWrap
        }
    }

    Widgets.ScrollBar {
        id: verticalScrollBar
        width: 10; height: view.height
        anchors.right: chatbox.right
        orientation: Qt.Vertical
        position: view.visibleArea.yPosition
        pageSize: view.visibleArea.heightRatio
    }
}