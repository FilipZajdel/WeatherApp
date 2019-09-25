#ifndef WEATHERLOGIC_H
#define WEATHERLOGIC_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>

struct WeatherInfo : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString ui_temperature READ ui_temperature)
    Q_PROPERTY(QString ui_humidity READ ui_humidity)
    Q_PROPERTY(QString ui_pressure READ ui_pressure)
    Q_PROPERTY(QString ui_windSpeed READ ui_windSpeed)
    Q_PROPERTY(QString ui_description READ ui_description)
    Q_PROPERTY(QString ui_cloudDescription READ ui_cloudDescription)
    Q_PROPERTY(QString ui_iconCode READ ui_iconCode)
    explicit WeatherInfo(QObject *parent=nullptr) : QObject(parent){}

    WeatherInfo(const WeatherInfo &w, QObject *parent = nullptr) :
        QObject(parent)
    {
        temperature = w.temperature;
        humidity = w.humidity;
        pressure = w.pressure;
        windSpeed = w.windSpeed;
        description = w.description;
        cloudDescription = w.cloudDescription;
        iconCode = w.iconCode;
    }

    WeatherInfo &operator=(const WeatherInfo &w)
    {
        temperature = w.temperature;
        humidity = w.humidity;
        pressure = w.pressure;
        windSpeed = w.windSpeed;
        description = w.description;
        cloudDescription = w.cloudDescription;
        iconCode = w.iconCode;
        return *this;
    }

    QString temperature;
    QString humidity;
    QString pressure;
    QString windSpeed;
    QString description;
    QString cloudDescription;
    QString iconCode;

    QString ui_temperature() const {
        return temperature;
    }
    QString ui_humidity() const {
        return humidity;
    }
    QString ui_pressure() const {
        return pressure;
    }
    QString ui_description() const {
        return description;
    }
    QString ui_cloudDescription() const {
        return cloudDescription;
    }
    QString ui_iconCode() const {
        return iconCode;
    }
    QString ui_windSpeed() const {
        return windSpeed;
    }
};

class WeatherLogic : public QObject
{
    Q_OBJECT
public:
    explicit WeatherLogic(QObject *parent = nullptr);
    void queryData(QString queryCity);

signals:
    void weatherUpdated(WeatherInfo weatherInfo);
//    void weatherUpdated(QVariantList weatherInfo);
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
