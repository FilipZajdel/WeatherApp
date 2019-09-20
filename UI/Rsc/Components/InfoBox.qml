import QtQuick 2.9
import QtQuick.Controls 2.2

Rectangle {
    property string mainText: ""
    property string secondaryText: ""
    property string backgroundColor: "#fefefe"
    id: rect
    color: backgroundColor

    Row {
        height: parent.height
        width: parent.width

        Rectangle {
            id: imageWrapper
            width: parent.width/2
            height: parent.height
            color: rect.color

            Image {
                source: "qrc:/Icons/greetings_view_image"
                width: sourceSize.width < parent.width ? sourceSize.width : parent.width
                height: sourceSize.height < parent.height ? sourceSize.height : parent.height
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Column {
            width: parent.width/2
            height: parent.height

            Text {
                id: mainText_

                text: rect.mainText
                width: parent.width
                height: parent.height/2
                font.pixelSize: 25
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                id: secondaryText_

                text: rect.secondaryText
                width: parent.width
                height: parent.height/2
                font.pixelSize: 15
                color: "gray"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
