#ifndef WEATHERCONTROLLER_H
#define WEATHERCONTROLLER_H

#include "../Logic/weatherlogic.h"

#include <QObject>
#include <QString>

class WeatherController : public QObject
{
    Q_OBJECT
public:
    explicit WeatherController(QObject *parent=nullptr) :
        QObject(parent) {}
    explicit WeatherController(WeatherLogic *weatherLogic);
    void setLogic(WeatherLogic *weatherLogic) {
        this->weatherLogic = weatherLogic;
    }

signals:
    void weatherUpdated(WeatherInfo weatherInfo);
    void weatherUpdated(WeatherInfo *weatherInfo);
    void briefInfoUpdated(QString iconCode, QString temperature, QString description);
    void invalidQuery();

public slots:
    void queryData(QString query);
    void logicDataUpdated(WeatherInfo weatherInfo);

private:
    WeatherLogic *weatherLogic;
};

#endif // WEATHERCONTROLLER_H
