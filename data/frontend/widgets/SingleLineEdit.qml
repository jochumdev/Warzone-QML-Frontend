import QtQuick 1.0

Rectangle {
    width: parent.width
    height: 29
    color: "#000161"
    border.color: "#0015f0"
    border.width: 1

    property alias text: textEdit.text
    property alias textColor: textEdit.color
    property alias readOnly: textEdit.readOnly

    TextInput {
        id: textEdit
        anchors.fill: parent
        anchors.leftMargin: 3; anchors.rightMargin: 3
        anchors.topMargin: 8

        color: "#aeaeb7"
        smooth: true
        font.family: "DejaVu Sans"
        font.pointSize: 9
        // font.letterSpacing: -0.3
    }
}