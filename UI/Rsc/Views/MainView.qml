import QtQuick 2.9
import QtQuick.Window 2.2
import Components 1.0

Window {
    id: window
    visible: true
    width: 480
    height: 480
    color: "#CCCCCC"

    Column {
        width: parent.width
        height: parent.height

        TextBox {
            id: textBox
            width: parent.width
            height: parent.height/4
            backgroundColor: window.color
        }

        InfoBox {
            id: infoBox
            width: parent.width
            height: parent.height/4
            mainText: "MainText"
            secondaryText: "SecondaryText"
            backgroundColor: window.color
        }

        Row {
            width: parent.width
            height: parent.height/4
            FlyingBox {
                id: pressureIndicator
                width: parent.width/2
                height: parent.height
                filePath: "qrc:/Icons/pressure_icon"
                hiddenText: "pressure"
                backgroundColor: window.color
            }

            FlyingBox {
                id: windIndicator
                width: parent.width/2
                height: parent.height
                filePath: "qrc:/Icons/wind_icon"
                hiddenText: "wind"
                backgroundColor: window.color
            }
        }
        Row {
            width: parent.width
            height: parent.height/4
            FlyingBox {
                id: humidityIndicator
                width: parent.width/2
                height: parent.height
                filePath: "qrc:/Icons/humidity_icon"
                hiddenText: "humidity"
                backgroundColor: window.color
            }

            FlyingBox {
                id: cloudinessDescription
                width: parent.width/2
                height: parent.height
                filePath: "qrc:/Icons/cloudiness_icon"
                hiddenText: "clouds"
                backgroundColor: window.color
            }
        }
    }
}
