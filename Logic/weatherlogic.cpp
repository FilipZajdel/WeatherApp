#include "weatherlogic.h"

#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QFileInfo>

//#define GET_NEW_DATA

WeatherLogic::WeatherLogic(QObject *parent) : QObject(parent)
{
    configurePaths();
    makeConnections();
}

void WeatherLogic::queryData(QString queryCity)
{
#ifdef GET_NEW_DATA
    getWeatherToFile(queryCity);
#else
    latestQuery = queryCity;
    queryFinished(1,(QProcess::ExitStatus)1);
#endif
}

void WeatherLogic::queryFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    qDebug() << "Query Finished";

    if(!dataFileExists()){
        qDebug() << "Logic IO Error";
        emit LogicIOError();
        return;
    }

    if(!fileValid()){
        qDebug() << "File invalid";
        emit invalidQuery();
        return;
    }

    WeatherInfo weatherInfo = getWeatherInfoFromFile();
    emit weatherUpdated(weatherInfo);
}

void WeatherLogic::configurePaths()
{
    weatherFilePath = "/home/filip/Projects/weather_api";
    weatherFileName = "weather";
    gettingWeatherScript = "/home/filip/Projects/weather_api/weather_service.py";
    scriptParams << "--path";
    scriptParams << weatherFilePath;
    scriptParams << "--city";
}

void WeatherLogic::makeConnections()
{
    connect(&pythonProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(queryFinished(int, QProcess::ExitStatus)));
}

void WeatherLogic::getWeatherToFile(QString city)
{
    latestQuery = city;
    QStringList params{gettingWeatherScript};

    qDebug() << "Invoking script with params:";
    for(auto param: scriptParams) {
        qDebug() << param;
    }

    params << scriptParams;
    params << city;

    pythonProcess.start("python3", params);
}

QString WeatherLogic::KelvinsToCelsius(QString tempKelvin)
{
    double temperature = tempKelvin.toDouble() - 273;
    return QString::number(temperature);
}

bool WeatherLogic::dataFileExists()
{
    QFileInfo fileToCheck(weatherFilePath+"/"+weatherFileName);
    qDebug() << "File path is: " << weatherFilePath + "/" +weatherFileName;
    return fileToCheck.exists() && fileToCheck.isFile();
}

bool WeatherLogic::fileValid()
{
    // performs check if file contains proper query name,for the sake of simplicity, name of the city
    QFile weatherFile(weatherFilePath+"/"+weatherFileName);
    weatherFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString weatherDataJson = weatherFile.readAll();
    weatherFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(weatherDataJson.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();
    QString savedCity = jsonObject.value("name").toString();

    qDebug() << "city name from file: " << jsonObject.value("name").toString();
    return latestQuery == savedCity;
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
            weatherInfo.temperature = KelvinsToCelsius(QString::number(jsonObject.value(jsonKey).toDouble()));
            weatherInfo.temperature += "\u00B0 C";
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
        } else if ("description" == jsonKey) {
            weatherInfo.cloudDescription = jsonObject.value(jsonKey).toString();
        } else if ("icon" == jsonKey) {
            weatherInfo.iconCode = jsonObject.value(jsonKey).toString();
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
