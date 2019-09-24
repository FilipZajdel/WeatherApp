import QtQuick 2.9
import QtQuick.Window 2.2
import Components 1.0

Window {
    id: window
    visible: true
    width: 320
    height: 320
    color: "#FEFEDD"
    title: qsTr("Weatherpp")

    Connections {
        target: textBox
        onTextEntered: weatherController.queryData(query)
    }

    Connections {
        target: weatherController
        onInvalidQuery: {
            humidityIndicator.hiddenText = "No data"
            pressureIndicator.hiddenText = "No data"
            windIndicator.hiddenText = "No data"
            cloudinessDescription.hiddenText = "No data"
        }

        onBriefInfoUpdated: {
            infoBox.mainText = temperature
            infoBox.secondaryText = description
        }

        onWeatherUpdated: {
            humidityIndicator.hiddenText = weatherInfo.ui_humidity
            pressureIndicator.hiddenText = weatherInfo.ui_pressure
            windIndicator.hiddenText = weatherInfo.ui_windSpeed
            cloudinessDescription.hiddenText = weatherInfo.ui_description
        }
    }

    Rectangle {
        anchors.fill: parent
        width: parent.width
        height: parent.height
        Image {
            anchors.fill: parent
            width: parent.width/2
            height: parent.height/2
            source: "qrc:/Icons/background_image"
            opacity: 0.15
        }

    Column {
        width: parent.width
        height: parent.height

        TextBox {
            id: textBox
            width: parent.width
            height: parent.height/4
            backgroundColor: "transparent"
            initialText: "Insert your city"
        }

        InfoBox {
            id: infoBox
            width: parent.width
            height: parent.height/4
            mainText: ""
            secondaryText: ""
            backgroundColor: "transparent"
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
                backgroundColor: "transparent"
            }

            FlyingBox {
                id: windIndicator
                width: parent.width/2
                height: parent.height
                filePath: "qrc:/Icons/wind_icon"
                hiddenText: "wind"
                backgroundColor: "transparent"
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
                backgroundColor: "transparent"
            }

            FlyingBox {
                id: cloudinessDescription
                width: parent.width/2
                height: parent.height
                filePath: "qrc:/Icons/cloudiness_icon"
                hiddenText: "clouds"
                backgroundColor: "transparent"
            }
        }
    }
    }
}
