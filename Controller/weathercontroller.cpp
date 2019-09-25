#include "weathercontroller.h"
#include <QDebug>

WeatherController::WeatherController(WeatherLogic *weatherLogic) : weatherLogic(weatherLogic)
{

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
    emit weatherUpdated(data);
    WeatherInfo *wInfo = new WeatherInfo{data, this};

    emit weatherUpdated(wInfo);
    emit briefInfoUpdated(data.iconCode, data.temperature, data.description);
}

