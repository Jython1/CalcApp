import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    anchors.fill: parent

    // Background rectangle filling the entire parent
    Rectangle {
        anchors.fill: parent
        color: "#024873"  // App background color
        z: -1             // Place behind other items
    }

    // Property holding the main display text (calculation result)
    property string displayText: calcLogic.result

    // Property holding the secondary display text (current expression)
    property string secondaryText: calcLogic.expression

    // Function to create and show a new secret window popup
    function openNewSecretWindow() {
        var component = Qt.createComponent("SecretWindow.qml");
        if (component.status === Component.Ready) {
            // Create new SecretWindow object as a child of root, positioned at (100, 100)
            var window = component.createObject(root, { x: 100, y: 100 });
            if (window === null) {
                console.log("Failed to create SecretWindow");
            } else {
                window.open(); // Show the SecretWindow popup
            }
        } else {
            console.log("Component not ready: " + component.errorString());
        }
    }

    // Connection to listen for the 'openSecretWindow' signal from calcLogic object
    Connections {
        target: calcLogic
        function onOpenSecretWindow() {
            openNewSecretWindow();
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        // Display area showing expression and result
        Rectangle {
            width: 320
            height: 160
            color: "#04BFAD"  // Display background color
            radius: 12        // Rounded corners

            Column {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 20

                // Text showing the current expression with lower opacity
                Text {
                    text: secondaryText
                    font.family: "OpenSans"
                    font.pixelSize: 30
                    color: "white"
                    opacity: 0.7
                    horizontalAlignment: Text.AlignRight
                    anchors.right: parent.right
                }

                // Text showing the calculation result prominently
                Text {
                    text: displayText
                    font.family: "OpenSans"
                    font.pixelSize: 50
                    font.weight: Font.Light
                    color: "white"
                    horizontalAlignment: Text.AlignRight
                    anchors.right: parent.right
                }
            }
        }

        // Calculator buttons arranged in a 4-column grid
        GridLayout {
            columns: 4
            rowSpacing: 27
            columnSpacing: 27

            // Each CalcButton represents a calculator key with styling and click handlers
            CalcButton { text: "()"; bgColor: "#0889A6"; pressedColor: "#F7E425"; onClicked: calcLogic.Append("(") }
            CalcButton { text: "+/-"; bgColor: "#0889A6"; pressedColor: "#F7E425"; onClicked: calcLogic.Append("-") }
            CalcButton { text: "%"; bgColor: "#0889A6"; pressedColor: "#F7E425"; onClicked: calcLogic.Append("%") }
            CalcButton { text: "÷"; bgColor: "#0889A6"; pressedColor: "#F7E425"; onClicked: calcLogic.Append("/") }

            CalcButton { text: "7"; bgColor: "#B0D1D8"; pressedColor: "#04BFAD"; textColor: "#024873"; onClicked: calcLogic.Append("7") }
            CalcButton { text: "8"; bgColor: "#B0D1D8"; pressedColor: "#04BFAD"; textColor: "#024873"; onClicked: calcLogic.Append("8") }
            CalcButton { text: "9"; bgColor: "#B0D1D8"; pressedColor: "#04BFAD"; textColor: "#024873"; onClicked: calcLogic.Append("9") }
            CalcButton { text: "×"; bgColor: "#0889A6"; pressedColor: "#F7E425"; onClicked: calcLogic.Append("*") }

            CalcButton { text: "4"; bgColor: "#B0D1D8"; pressedColor: "#04BFAD"; textColor: "#024873"; onClicked: calcLogic.Append("4") }
            CalcButton { text: "5"; bgColor: "#B0D1D8"; pressedColor: "#04BFAD"; textColor: "#024873"; onClicked: calcLogic.Append("5") }
            CalcButton { text: "6"; bgColor: "#B0D1D8"; pressedColor: "#04BFAD"; textColor: "#024873"; onClicked: calcLogic.Append("6") }
            CalcButton { text: "-"; bgColor: "#0889A6"; pressedColor: "#F7E425"; onClicked: calcLogic.Append("-") }

            CalcButton { text: "1"; bgColor: "#B0D1D8"; pressedColor: "#04BFAD"; textColor: "#024873"; onClicked: calcLogic.Append("1") }
            CalcButton { text: "2"; bgColor: "#B0D1D8"; pressedColor: "#04BFAD"; textColor: "#024873"; onClicked: calcLogic.Append("2") }
            CalcButton { text: "3"; bgColor: "#B0D1D8"; pressedColor: "#04BFAD"; textColor: "#024873"; onClicked: calcLogic.Append("3") }
            CalcButton { text: "+"; bgColor: "#0889A6"; pressedColor: "#F7E425"; onClicked: calcLogic.Append("+") }

            CalcButton { text: "C"; bgColor: "#F25E5E"; pressedColor: "#F5A6A6"; onClicked: calcLogic.Clear() }
            CalcButton { text: "0"; bgColor: "#B0D1D8"; pressedColor: "#04BFAD"; textColor: "#024873"; onClicked: calcLogic.Append("0") }
            CalcButton { text: "."; bgColor: "#B0D1D8"; pressedColor: "#04BFAD"; textColor: "#024873"; onClicked: calcLogic.Append(".") }

            // Equals button with additional press and hold event handlers
            CalcButton {
                text: "="
                bgColor: "#0889A6"
                pressedColor: "#F7E425"

                onClicked: calcLogic.Calculate()
                onPressed: calcLogic.startHoldTimer()
                onReleased: calcLogic.stopHoldTimer()
                onExited: calcLogic.stopHoldTimer()
            }
        }
    }
}
