import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    anchors.fill: parent

    //Background color
    Rectangle {
        anchors.fill: parent
        color: "#024873" // Background app color
        z: -1
    }


    property string displayText: calcLogic.result
    property string secondaryText: calcLogic.expression

    Column {
        anchors.centerIn: parent
        spacing: 10

        //Display area
        Rectangle {
            width: 320
            height: 160
            color: "#04BFAD" // Display color
            radius: 12

            Column {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 20

                Text {
                    text: secondaryText
                    font.family: "OpenSans"
                    font.pixelSize: 30
                    color: "white"
                    opacity: 0.7
                    horizontalAlignment: Text.AlignRight
                    anchors.right: parent.right
                }

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

        // Buttons
        GridLayout {
            columns: 4
            rowSpacing: 27
            columnSpacing: 27

            CalcButton { text: "()"; bgColor: "#0889A6"; pressedColor: "#F7E425"; onClicked: calcLogic.Append("(") }
            CalcButton { text: "+/-"; bgColor: "#0889A6"; pressedColor: "#F7E425"; onClicked: calcLogic.Append("-") }
            CalcButton { text: "%"; bgColor: "#0889A6"; pressedColor: "#F7E425"; onClicked: calcLogic.Append("%") }
            CalcButton { text: "÷"; bgColor: "#0889A6"; pressedColor: "#F7E425"; onClicked: calcLogic.Append("/") }

            CalcButton { text: "7"; bgColor:  "#B0D1D8"; pressedColor: "#04BFAD"; textColor: "#024873"; onClicked: calcLogic.Append("7") }
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
            CalcButton { text: "="; bgColor: "#0889A6"; pressedColor: "#F7E425"; onClicked: calcLogic.Calculate() }
        }
    }
}
