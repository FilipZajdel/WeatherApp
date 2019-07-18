#ifndef WEATHERLOGIC_H
#define WEATHERLOGIC_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>

struct WeatherInfo {

    QString temperature;
    QString humidity;
    QString pressure;
    QString windSpeed;
    QString description;
    QString cloudDescription;
};

class WeatherLogic : public QObject
{
    Q_OBJECT
public:
    explicit WeatherLogic(QObject *parent = nullptr);
    void queryData(QString queryCity);

signals:
    void weatherUpdated(WeatherInfo weatherInfo);

private:
    void configurePaths();
    void getWeatherToFile(QString city);

    // getting information from json -> to be moved to external class
    WeatherInfo getWeatherInfoFromFile();
    void getWindSpeedFromJson(QJsonObject jsonObject, WeatherInfo &weatherInfo);
    void getMainFromJson(QJsonObject jsonObject, WeatherInfo &weatherInfo);
    void getWeatherFromJson(QJsonArray jsonArray, WeatherInfo &weatherInfo);
    void fillWeatherInfoFromJson(QJsonObject jsonObject, WeatherInfo &weatherInfo);

    QString gettingWeatherScript;
    QStringList scriptParams;
    QString weatherFilePath;
    QString weatherFileName;
};

#endif // WEATHERLOGIC_H
