#include "weatherlogic.h"

#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QFileInfo>
#include <QChar>
#include <algorithm>

#define GET_NEW_DATA

class QueryValidator {
    public:
    virtual ~QueryValidator() {delete next;}
    void addValidator(QueryValidator *validator) {
        next = validator;
    }
    virtual void validate(QString &query){
        if(next) next->validate(query);
    }

    private:
    QueryValidator *next{nullptr};
};

class UpperCaseQueryValidator : public QueryValidator {
    public:
    void validate(QString &query) override {
        query[0] = query[0].toUpper();
        std::for_each(query.begin()+1, query.end(), [](QChar &c) {
            c = c.toLower();
        });

        QueryValidator::validate(query);
    }
};

WeatherLogic::WeatherLogic(QObject *parent) : QObject(parent)
{
    configurePaths();
    makeConnections();
}

void WeatherLogic::queryData(QString queryCity)
{
    QueryValidator queryValidator;
    queryValidator.addValidator(new UpperCaseQueryValidator);
    queryValidator.validate(queryCity);
#ifdef GET_NEW_DATA
    getWeatherToFile(queryCity);
#else
    latestQuery = queryCity;
    queryFinished(0, QProcess::NormalExit);
#endif
}

void WeatherLogic::queryFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    qDebug() << "Query Finished";

    if(!dataFileExists()){
        emit LogicIOError();
        qDebug() << "File doesn't exist";
        return;
    }

    if(!fileValid()){
        emit invalidQuery();
        qDebug() << "Invalid query";
        return;
    }

    qDebug() << "emit weatherUpdated";
    WeatherInfo weatherInfo = getWeatherInfoFromFile();
    emit weatherUpdated(weatherInfo);
}

void WeatherLogic::configurePaths()
{
    weatherFilePath = ".";
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

    qDebug() << "city name from file: " << jsonObject.value("name").toString()
             << "\n" << "Last Query was: " << latestQuery;
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
