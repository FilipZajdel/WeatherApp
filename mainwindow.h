#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "weathercontroller.h"

#include <QMainWindow>
#include <QLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(WeatherController *weatherController, QWidget *parent = nullptr);

private:
    QWidget *userInteracionWidget;
    QWidget *weatherWidget;
    QWidget *centralWidget;
    QLayout *layout;
    WeatherController *weatherController;

    void setAppereance();
    void makeConnections();
};

#endif // MAINWINDOW_H
