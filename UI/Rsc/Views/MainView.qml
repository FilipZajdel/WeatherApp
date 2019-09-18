import QtQuick 2.9
import QtQuick.Window 2.2
import Components 1.0

Window {
    visible: true
    width: 640
    height: 480

    Column {
        width: parent.width
        height: parent.height

        TextBox {
            id: textBox
        }

        InfoBox {
            id: infoBox
            mainText: "MainText"
            secondaryText: "SecondaryText"
        }
    }
}
