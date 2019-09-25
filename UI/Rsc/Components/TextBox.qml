import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: textBox
    signal textEntered(string query)
    property int fontSize: 22
    property string backgroundColor: "#fefefe"

    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: textBox.backgroundColor

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
                font.pixelSize: textBox.fontSize
                selectByMouse: true
                selectedTextColor: "black"
                selectionColor: "gray"

                onEditingFinished: {
                    stackView.replace(mouseArea)
                    textEntered(textInput.text)
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
                    font.pixelSize: textBox.fontSize
                }
            }
        }
    }
}
