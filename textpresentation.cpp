#include "textpresentation.h"
#include <QDebug>

TextPresentation::TextPresentation(QWidget *parent):QWidget(parent)
{
    label = new QLabel(this);
    configureLabel();
}

QSize TextPresentation::sizeHint() const
{
    return QSize(200, 50); // TODO: fix that
}

void TextPresentation::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit mousePressed();
    }

    qDebug() << "mouse in text presentation";
}

void TextPresentation::updateText(QString text)
{
    label->setText(text);
}

void TextPresentation::configureLabel()
{
    QFont font("Times", 12, QFont::Bold);
    label->setFont(font);
    label->setText("Click me!");
}

