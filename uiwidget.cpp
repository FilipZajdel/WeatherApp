#include "uiwidget.h"
#include <QDebug>


UIWidget::UIWidget(QWidget *parent) : QWidget(parent)
{
    queryLine = new QLineEdit;
    queryButton = new QPushButton;
    boxLayout = new QHBoxLayout;

    boxLayout->addWidget(queryLine);
    boxLayout->addWidget(queryButton);

    setLayout(boxLayout);

    configureWidgets();
    makeConnections();
}

UIWidget::~UIWidget()
{
    delete queryLine;
    delete queryButton;
    delete boxLayout;
}

void UIWidget::clicked()
{
    qDebug() << "clicked" << queryLine->text();
    emit queryData(queryLine->text());
}

void UIWidget::makeConnections()
{
    connect(queryButton, &QPushButton::clicked, this, &UIWidget::clicked);
}

void UIWidget::configureWidgets()
{
    if(queryLine){
        queryLine->setText("City");
    }

    if(queryButton){
        queryButton->setText("Get");
    }
}
