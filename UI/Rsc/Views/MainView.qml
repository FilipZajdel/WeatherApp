import QtQuick 2.9
import QtQuick.Window 2.2
import Components 1.0

Window {
    id: window
    visible: true
    width: 320
    height: 480
    title: "Weatherpp"

    Rectangle {
        anchors.fill: parent
        width: parent.width
        height: parent.height
        Image {
            anchors.fill: parent
            width: parent.width
            height: parent.height
            source: "qrc:/Icons/background"
            opacity: 0.15
        }
    }

    Connections {
        target: weatherController
        onWeatherUpdated: {
            pressureIndicator.updateHiddenText(weatherInfo.ui_pressure)
            windIndicator.updateHiddenText(weatherInfo.ui_windSpeed)
            humidityIndicator.updateHiddenText(weatherInfo.ui_humidity)
            cloudinessDescription.updateHiddenText(weatherInfo.ui_cloudDescription)
        }
        onBriefInfoUpdated: {
            infoBox.onValidQuery(temperature, description, "qrc:/Icons/"+iconCode)
        }

        onInvalidQuery: infoBox.onInvalidQuery("fucked up")
    }

    Connections {
        target: textBox
        onTextEntered: weatherController.queryData(query)
    }

    Column {
        width: parent.width
        height: parent.height

        TextBox {
            id: textBox
            width: parent.width
            height: parent.height/4
            backgroundColor: "transparent"
        }

        InfoBox {
            id: infoBox
            width: parent.width
            height: parent.height/4
            mainText: "Hello!"
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
