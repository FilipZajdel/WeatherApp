#include "weathercontroller.h"
#include <QDebug>

WeatherController::WeatherController(WeatherLogic *weatherLogic, QObject *parent) : weatherLogic(weatherLogic),
    QObject(parent)
{

}

void WeatherController::setLogic(WeatherLogic *logic) {
    logic = logic;
}

void WeatherController::queryData(QString query)
{
    if(query != ""){
        weatherLogic->queryData(query);
    }

    qDebug() << "WeatherController::quertData" << query << "data in weather controller";
}

void WeatherController::logicDataUpdated(WeatherInfo data)
{
    emit weatherUpdated(WeatherInfo(data, this));
    emit weatherUpdated(new WeatherInfo{data, this});
    emit briefInfoUpdated(data.iconCode, data.temperature, data.description);
}

