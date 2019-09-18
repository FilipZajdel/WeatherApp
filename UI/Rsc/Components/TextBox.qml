import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    width: 640
    height: 240
    signal textEntered()

    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: "lightgray"

        StackView {
            id: stackView
            anchors.fill: parent
            initialItem: mouseArea

            TextInput {
                id: textInput
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: "Your City"

                onEditingFinished: {
                    stackView.replace(mouseArea)
                    textEntered()
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    stackView.clear()
                    stackView.push(textInput)
                }
                Text {
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    id: textField
                    anchors.fill: parent
                    text: textInput.text
                }
            }
        }
    }
}
