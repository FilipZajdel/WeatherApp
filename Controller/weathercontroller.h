#ifndef WEATHERCONTROLLER_H
#define WEATHERCONTROLLER_H

#include "../Logic/weatherlogic.h"

#include <QObject>
#include <QString>

class WeatherController : public QObject
{
    Q_OBJECT
public:
    explicit WeatherController(WeatherLogic *weatherLogic);

signals:
    void weatherUpdated(WeatherInfo weatherInfo);
    void briefInfoUpdated(QString iconCode, QString temperature, QString description);
    void invalidQuery();

public slots:
    void queryData(QString query);
    void logicDataUpdated(WeatherInfo weatherInfo);

private:
    WeatherLogic *weatherLogic;
};

#endif // WEATHERCONTROLLER_H
