#include "weatherlogic.h"

#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>

#define GET_NEW_DATA

WeatherLogic::WeatherLogic(QObject *parent) : QObject(parent)
{
    configurePaths();
}

void WeatherLogic::queryData(QString queryCity)
{
#ifdef GET_NEW_DATA
    getWeatherToFile(queryCity);
#endif
    WeatherInfo weatherInfo = getWeatherInfoFromFile();
    qDebug() << "Temperature " << weatherInfo.temperature;
    emit weatherUpdated(getWeatherInfoFromFile());
}

void WeatherLogic::configurePaths()
{
    weatherFilePath = ".";
    weatherFileName = "weather";
    gettingWeatherScript = "/home/filip/Projects/PythonProjects/weatherApi/weather_service.py";
    scriptParams << "--path";
    scriptParams << weatherFilePath;
    scriptParams << "--city";
}

void WeatherLogic::getWeatherToFile(QString city)
{
    QProcess pythonProcess;
    QStringList params{gettingWeatherScript};

    params << scriptParams;
    params << city;

    pythonProcess.startDetached("python3", params);
    pythonProcess.waitForFinished();
    pythonProcess.close();
}

WeatherInfo WeatherLogic::getWeatherInfoFromFile()
{
    QFile weatherFile(weatherFilePath+"/"+weatherFileName);
    weatherFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString weatherDataJson = weatherFile.readAll();
    weatherFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(weatherDataJson.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();

    WeatherInfo weatherInfo;
    fillWeatherInfoFromJson(jsonObject ,weatherInfo);

    return weatherInfo;
}

void WeatherLogic::getWindSpeedFromJson(QJsonObject jsonObject, WeatherInfo &weatherInfo)
{
   weatherInfo.windSpeed = QString::number(jsonObject.value("speed").toDouble()) + "m/s";
}

void WeatherLogic::getMainFromJson(QJsonObject jsonObject, WeatherInfo &weatherInfo)
{
    foreach(const QString& jsonKey, jsonObject.keys()){
        if("temp" == jsonKey){
            weatherInfo.temperature = QString::number(jsonObject.value(jsonKey).toDouble());
            weatherInfo.temperature += " *C";
        } else if ("pressure" == jsonKey) {
            weatherInfo.pressure = QString::number(jsonObject.value(jsonKey).toDouble());
            weatherInfo.pressure += " hPa";
        } else if ("humidity" == jsonKey) {
            weatherInfo.humidity = QString::number(jsonObject.value(jsonKey).toDouble());
            weatherInfo.humidity += " %";
        }
    }
}

void WeatherLogic::getWeatherFromJson(QJsonArray jsonArray, WeatherInfo &weatherInfo)
{
    QJsonObject jsonObject = (jsonArray[0].toArray())[0].toObject();

    foreach(const QString& jsonKey, jsonObject.keys()){

        if("main" == jsonKey){
            weatherInfo.description = jsonObject.value(jsonKey).toString();
//            qDebug() << "main(description)" << jsonObject.value(jsonKey).toString();
        } else if ("description" == jsonKey) {
//            qDebug() << "descripion(cloudDescription)" << jsonObject.value(jsonKey).toString();
            weatherInfo.cloudDescription = jsonObject.value(jsonKey).toString();
        }
    }
}

void WeatherLogic::fillWeatherInfoFromJson(QJsonObject jsonObject, WeatherInfo &weatherInfo)
{
    foreach(const QString& jsonKey, jsonObject.keys()){

        if("main" == jsonKey) {
            getMainFromJson(jsonObject.value(jsonKey).toObject(), weatherInfo);
        } else if ("weather" == jsonKey) {
            QJsonArray jsonArray{jsonObject.value(jsonKey)};
            getWeatherFromJson(jsonArray, weatherInfo);
        } else if ("wind" == jsonKey) {
            getWindSpeedFromJson(jsonObject.value(jsonKey).toObject(), weatherInfo);
        }
    }
}
