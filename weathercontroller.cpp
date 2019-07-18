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

    qDebug() << "query data in weather controller";
}

void WeatherController::logicDataUpdated(WeatherInfo data)
{
   emit weatherUpdated(data);
}
