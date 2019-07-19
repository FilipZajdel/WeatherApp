#include "weatherspec.h"

const QString pressureIcon = "/home/filip/widgets/UI/Rsc/Icons/test_icon";
const QString humidityIcon = "/home/filip/widgets/UI/Rsc/Icons/test_icon";
const QString windSpeedIcon = "/home/filip/widgets/UI/Rsc/Icons/test_icon";
const QString cloudinessIcon = "/home/filip/widgets/UI/Rsc/Icons/test_icon";


WeatherSpec::WeatherSpec(QWidget *parent) : QWidget(parent)
{
    configureWidgets();
    this->setLayout(&vLayout);
}

QSize WeatherSpec::sizeHint() const
{
    return QSize(400, 400);
}

void WeatherSpec::updateDescriptions(WeatherInfo weatherInfo)
{
    pressure.setHiddenText(weatherInfo.pressure);
    humidity.setHiddenText(weatherInfo.humidity);
    windSpeed.setHiddenText(weatherInfo.windSpeed);
    cloudiness.setHiddenText(weatherInfo.cloudDescription);
}

void WeatherSpec::configureWidgets()
{
    pressure.setIcon(pressureIcon);
    humidity.setIcon(humidityIcon);
    windSpeed.setIcon(windSpeedIcon);
    cloudiness.setIcon(cloudinessIcon);

    pressure.setHiddenText("Pressure");
    humidity.setHiddenText("Humidity");
    windSpeed.setHiddenText("Wind Speed");
    cloudiness.setHiddenText("Cloudiness");

    hLayouts[0].addWidget(&humidity);
    hLayouts[0].addWidget(&pressure);
    hLayouts[1].addWidget(&cloudiness);
    hLayouts[1].addWidget(&windSpeed);

    for(auto &layout : hLayouts){
        vLayout.addLayout(&layout);
    }
}
