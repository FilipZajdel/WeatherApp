#include "mainwindow.h"
#include "uiwidget.h"
#include "weatherwidget.h"

#include <QDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(WeatherController *weatherController, QWidget *parent) : QMainWindow(parent)
{
    weatherWidget = new WeatherWidget;
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
}

void MainWindow::makeConnections()
{
    // widgets
    connect(userInteracionWidget, SIGNAL(queryData(QString)), weatherController, SLOT(queryData(QString)));

    // logic
    connect(weatherController, SIGNAL(weatherUpdated(WeatherInfo)), weatherWidget, SLOT(update(WeatherInfo)));
}
