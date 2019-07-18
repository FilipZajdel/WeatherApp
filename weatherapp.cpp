#include "mainwindow.h"
#include "weatherapp.h"
#include "uiwidget.h"

WeatherApp::WeatherApp(QObject *parent) : QObject(parent)
{
    weatherLogic = new WeatherLogic;
    weatherController = new WeatherController(weatherLogic);
    mainWindow = new MainWindow(weatherController);

    makeConnections();
}

WeatherApp::~WeatherApp(){
    delete weatherLogic;
    delete weatherController;
    delete mainWindow;
}

void WeatherApp::run()
{
    mainWindow->show();
}

void WeatherApp::makeConnections()
{
   connect(weatherLogic, SIGNAL(weatherUpdated(WeatherInfo)), weatherController, SLOT(logicDataUpdated(WeatherInfo)));
}

