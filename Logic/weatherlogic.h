#ifndef WEATHERLOGIC_H
#define WEATHERLOGIC_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>

struct WeatherInfo : public QObject {
Q_OBJECT
public:
    explicit WeatherInfo(QObject *parent = nullptr) : QObject(parent) {
    }
    WeatherInfo(const WeatherInfo &w, QObject *parent=nullptr) :
        QObject(parent) {

        temperature = w.temperature;
        humidity = w.humidity;
        pressure = w.pressure;
        windSpeed = w.windSpeed;
        description = w.description;
        cloudDescription = w.cloudDescription;
        iconCode = w.iconCode;
    }

    WeatherInfo &operator=(const WeatherInfo &w) {

        temperature = w.temperature;
        humidity = w.humidity;
        pressure = w.pressure;
        windSpeed = w.windSpeed;
        description = w.description;
        cloudDescription = w.cloudDescription;
        iconCode = w.iconCode;
    }


    Q_PROPERTY(QString ui_humidity READ ui_humidity)
    QString ui_humidity(){
        return humidity;
    }
    Q_PROPERTY(QString ui_pressure READ ui_pressure)
    QString ui_pressure(){
        return pressure;
    }
    Q_PROPERTY(QString ui_windSpeed READ ui_windSpeed)
    QString ui_windSpeed(){
        return windSpeed;
    }
    Q_PROPERTY(QString ui_description READ ui_description)
    QString ui_description(){
        return description;
    }
    Q_PROPERTY(QString ui_cloudDescription READ ui_cloudDescription)
    QString ui_cloudDescription(){
        return cloudDescription;
    }

    QString temperature;
    QString humidity;
    QString pressure;
    QString windSpeed;
    QString description;
    QString cloudDescription;
    QString iconCode;
};

class WeatherLogic : public QObject
{
    Q_OBJECT
public:
    explicit WeatherLogic(QObject *parent = nullptr);
    void queryData(QString queryCity);

signals:
    void weatherUpdated(WeatherInfo weatherInfo);
    void invalidQuery(); // TODO: emit it when necessary
    void LogicIOError();

private slots:
    void queryFinished(int, QProcess::ExitStatus);

private:
    void configurePaths();
    void makeConnections();
    void getWeatherToFile(QString city);
    QString KelvinsToCelsius(QString tempKelvin);

    // getting information from json -> to be moved to external class
    bool dataFileExists();
    bool fileValid();

    /** /brief Takes data from json file.
     *
     * In case of invalid file, emits invalidQuery() signal */
    WeatherInfo getWeatherInfoFromFile();
    void getWindSpeedFromJson(QJsonObject jsonObject, WeatherInfo &weatherInfo);
    void getMainFromJson(QJsonObject jsonObject, WeatherInfo &weatherInfo);
    void getWeatherFromJson(QJsonArray jsonArray, WeatherInfo &weatherInfo);
    void fillWeatherInfoFromJson(QJsonObject jsonObject, WeatherInfo &weatherInfo);

    QString latestQuery;
    QProcess pythonProcess;
    QString gettingWeatherScript;
    QStringList scriptParams;
    QString weatherFilePath;
    QString weatherFileName;
};

#endif // WEATHERLOGIC_H
