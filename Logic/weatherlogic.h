#ifndef WEATHERLOGIC_H
#define WEATHERLOGIC_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>

struct WeatherInfo {

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
