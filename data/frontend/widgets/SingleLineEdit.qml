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
        color: "#aeaeb7"
        width: parent.width
        id: textEdit
        font.family: "DejaVu Sans"
        font.pixelSize: 12
        font.letterSpacing: -0.3
        x: 3; y: 8
    }
}