import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: button

    // Button text, aliased to the text property of the internal Text element (label)
    property alias text: label.text

    // Background color of the button in normal state
    property color bgColor: "#3498db"

    // Background color of the button when pressed
    property color pressedColor: "#1e90ff"

    // Text color of the button
    property color textColor: "white"

    // Signals emitted on user interaction with the button
    signal clicked()   // Emitted when mouse is released inside the button
    signal pressed()   // Emitted when mouse button is pressed down on the button
    signal released()  // Emitted when mouse button is released (anywhere)
    signal exited()    // Emitted when mouse cursor leaves the button area

    // Implicit size of the button
    implicitWidth: 60
    implicitHeight: 60

    // Corner radius makes the button circular (half of height)
    radius: height / 2

    // Button color changes depending on pressed state
    color: mouseArea.pressed ? pressedColor : bgColor

    Text {
        id: label
        anchors.centerIn: parent

        // Text color
        color: textColor

        // Font size in pixels
        font.pixelSize: 24

        // Bold font style
        font.bold: true

        // Horizontally center text
        horizontalAlignment: Text.AlignHCenter

        // Vertically center text
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent  // Fill entire button area
        hoverEnabled: true     // Enable hover events

        onPressed: {
            button.pressed()  // Emit pressed signal on mouse press
        }
        onReleased: {
            button.released() // Emit released signal on mouse release

            // If mouse is released inside the button, emit clicked signal
            if (containsMouse) {
                button.clicked()
            }
        }
        onExited: {
            button.exited()   // Emit exited signal when mouse leaves button
        }
    }
}
