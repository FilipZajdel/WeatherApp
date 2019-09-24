#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "WeatherApp/weatherapp.h"

int _main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WeatherApp weatherApp;
    weatherApp.run();

    return a.exec();
}

int main(int argc, char *argv[]){
    QGuiApplication app(argc, argv);
    qmlRegisterType<WeatherController> ("WC", 1, 0, "WeatherController");
    qmlRegisterType<WeatherInfo> ("WC", 1, 0, "WeatherInfo");

    WeatherLogic weatherLogic;
    WeatherController weatherController(&weatherLogic);

    QObject::connect(&weatherLogic, SIGNAL(weatherUpdated(WeatherInfo)), &weatherController, SLOT(logicDataUpdated(WeatherInfo)));
    QObject::connect(&weatherLogic, SIGNAL(invalidQuery()), &weatherController, SIGNAL(invalidQuery()));

    QQmlApplicationEngine qmlEngine;
    qmlEngine.addImportPath("qrc:/");

    qmlEngine.rootContext()->setContextProperty("weatherController", &weatherController);

    qmlEngine.load(QUrl(QStringLiteral("qrc:/Views/MainView.qml")));
    if(qmlEngine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
