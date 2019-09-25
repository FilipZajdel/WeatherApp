#include "weathercontroller.h"
#include <QDebug>

WeatherController::WeatherController(WeatherLogic *weatherLogic) : WeatherController()
{
    weatherLogic = weatherLogic;
}

void WeatherController::queryData(QString query)
{
    if(query != ""){
        weatherLogic->queryData(query);
    }

    qDebug() << "Query: " << query << "in WeatherController::queryData";
}

void WeatherController::logicDataUpdated(WeatherInfo data)
{
    *weatherInfo = data;
    emit weatherUpdated(data);
    emit ui_weatherUpdated();
    emit briefInfoUpdated(data.iconCode, data.temperature, data.description);
}

