#include <QApplication>
#include "weatherapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WeatherApp weatherApp;
    weatherApp.run();

    return a.exec();
}
