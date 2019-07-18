#include "mainwindow.h"
#include "uiwidget.h"
#include "weatherwidget.h"

#include <QDebug>
#include <QHBoxLayout>

MainWindow::MainWindow(WeatherController *weatherController, QWidget *parent) : QMainWindow(parent)
{
    weatherWidget = new WeatherWidget;
    userInteracionWidget = new UIWidget;
    centralWidget = new QWidget;
    layout = new QHBoxLayout;
    this->weatherController = weatherController;

    makeConnections();
    setAppereance();
}

void MainWindow::setAppereance()
{
    layout->addWidget(weatherWidget);
    layout->addWidget(userInteracionWidget);

    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);
}

void MainWindow::makeConnections()
{
    // widgets
    connect(userInteracionWidget, SIGNAL(queryData(QString)), weatherController, SLOT(queryData(QString)));

    // logic
    connect(weatherController, SIGNAL(weatherUpdated(WeatherInfo)), weatherWidget, SLOT(update(WeatherInfo)));
}
