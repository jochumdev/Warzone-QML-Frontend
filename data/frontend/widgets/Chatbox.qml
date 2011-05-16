import QtQuick 1.0
import "../widgets" as Widgets

Item {
    id: chatbox
    anchors.fill: parent

    property string textColor: "black"
    property int margins: 2

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
            text: "This is a lot of text and some more and more <b>0123456789</b> <i>0123456789</i> 0123456789 0123456789 0123456789<br>...<br>...<br>...<br>...<br>...<br>...<br>"
        }
    }

    Widgets.ScrollBar {
        id: verticalScrollBar
        width: 10; height: view.height
        anchors.right: chatbox.right
        opacity: 1
        orientation: Qt.Vertical
        position: view.visibleArea.yPosition
        pageSize: view.visibleArea.heightRatio
    }
}