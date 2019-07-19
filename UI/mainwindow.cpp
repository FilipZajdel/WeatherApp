#include "mainwindow.h"
#include "Widgets/uiwidget.h"
//#include "Widgets/weatherwidget.h"
#include "Widgets/weatherspec.h"

#include <QDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(WeatherController *weatherController, QWidget *parent) : QMainWindow(parent)
{
    weatherWidget = new WeatherSpec;
    userInteracionWidget = new UIWidget;
    centralWidget = new QWidget;
    layout = new QVBoxLayout;
    this->weatherController = weatherController;

    makeConnections();
    setAppereance();
}

void MainWindow::setAppereance()
{
    layout->addWidget(userInteracionWidget);
    layout->addWidget(weatherWidget);

    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);

    layout->setAlignment(userInteracionWidget, Qt::AlignCenter);
    layout->setAlignment(weatherWidget, Qt::AlignCenter);
}

void MainWindow::makeConnections()
{
    // widgets
    connect(userInteracionWidget, SIGNAL(queryData(QString)), weatherController, SLOT(queryData(QString)));
    // logic
    connect(weatherController, SIGNAL(weatherUpdated(WeatherInfo)), weatherWidget, SLOT(updateDescriptions(WeatherInfo)));
}
