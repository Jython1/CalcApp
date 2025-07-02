import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: root
    width: 300
    height: 200
    modal: true
    focus: true

    Rectangle {
        anchors.fill: parent
        color: "#333"
        radius: 12

        Column {
            anchors.centerIn: parent
            spacing: 20

            Text {
                text: "Секретное меню"
                color: "white"
                font.pixelSize: 24
                horizontalAlignment: Text.AlignHCenter
            }

            Button {
                text: "Закрыть"
                onClicked: root.close()
            }
        }
    }

    onClosed: {
        root.destroy();
    }
}
