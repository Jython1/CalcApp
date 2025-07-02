import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: button
    property alias text: label.text
    property color bgColor: "#3498db"
    property color pressedColor: "#1e90ff"
    property color textColor: "white"

    signal clicked()

    implicitWidth: 60
    implicitHeight: 60
    radius: height / 2
    color: mouseArea.pressed ? pressedColor : bgColor

    Text {
        id: label
        anchors.centerIn: parent
        color: textColor
        font.pixelSize: 24
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: button.clicked()
    }
}
