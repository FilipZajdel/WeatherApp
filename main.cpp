#include <QApplication>
#include "WeatherApp/weatherapp.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WeatherApp weatherApp;
    weatherApp.run();

    return a.exec();
}


//#include <QLineEdit>
//#include <QHBoxLayout>
//#include <QVBoxLayout>

//#include "UI/Widgets/flyingbox.h"

//int main(int argc, char *argv[]){
//    QApplication a(argc, argv);
//    QWidget widget;

//    QHBoxLayout *hLayouts = new QHBoxLayout[2];
//    QVBoxLayout *vLayout = new QVBoxLayout;
//    FlyingBox flyingBoxFirstRow[3];
//    FlyingBox flyingBoxSecondRow[3];

//    for(auto &widget : flyingBoxFirstRow){
//        widget.setIcon("/home/filip/widgets/UI/Rsc/Icons/test_icon");
//        widget.setHiddenText("It is first row");
//        hLayouts[0].addWidget(&widget);
//    }

//    for(auto &widget : flyingBoxSecondRow){
//        widget.setIcon("/home/filip/widgets/UI/Rsc/Icons/test_icon");
//        widget.setHiddenText("It is second row");
//        hLayouts[1].addWidget(&widget);
//    }

//    vLayout->addLayout(&hLayouts[0]);
//    vLayout->addLayout(&hLayouts[1]);
//    widget.setLayout(vLayout);

//    widget.show();
//    return a.exec();
//}

//#include "UI/Widgets/weatherspec.h"
//#include <QHBoxLayout>


//int main(int argc, char *argv[]){
//    QApplication a(argc, argv);
//    WeatherSpec weatherSpec;

//    weatherSpec.show();
//    return a.exec();
//}
