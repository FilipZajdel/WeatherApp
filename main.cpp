#include <QApplication>
#include "weatherapp.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WeatherApp weatherApp;
    weatherApp.run();

    return a.exec();
}


//#include "texteditor.h"
//#include <QLineEdit>
//#include <QHBoxLayout>
//#include <QMainWindow>

//int main(int argc, char *argv[]){
//    QApplication a(argc, argv);
//    QMainWindow mainWindow;

//    TextEditor textEditor;
//    QLineEdit lineEdit;
//    QHBoxLayout *layout = new QHBoxLayout;

//    layout->addWidget(&textEditor);

//    mainWindow.show();

//    return a.exec();
//}
