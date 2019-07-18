#include "uiwidget.h"
#include <QDebug>


UIWidget::UIWidget(QWidget *parent) : QWidget(parent)
{
    textEditor = new TextEditor(this);
    textPresentation = new TextPresentation(this);
    boxLayout = new QHBoxLayout;
    stackedWidget = new QStackedWidget();

    stackedWidget->addWidget(textEditor);
    stackedWidget->addWidget(textPresentation);

    boxLayout->addWidget(stackedWidget);
    setLayout(boxLayout);

    configureWidgets();
    makeConnections();

    widgetState = PRESENTATION;
    stackedWidget->setCurrentWidget(textPresentation);
}

UIWidget::~UIWidget()
{
    delete textEditor;
    delete textPresentation;
    delete stackedWidget;
    delete boxLayout;
}

void UIWidget::newQuery(QString query)
{
    qDebug() << "clicked " << query;
    emit queryData(query);
}

void UIWidget::switchToTextEditor()
{
    stackedWidget->setCurrentWidget(textEditor);
}

void UIWidget::switchToTextPresentation()
{
    stackedWidget->setCurrentWidget(textPresentation);
}

void UIWidget::makeConnections()
{
    connect(textEditor, &TextEditor::textInserted, this, &UIWidget::newQuery);
    connect(textEditor, &TextEditor::textInserted, textPresentation, &TextPresentation::updateText);
    connect(textPresentation, &TextPresentation::mousePressed, this, &UIWidget::switchToTextEditor);
    connect(textEditor, &TextEditor::textInserted, this, &UIWidget::switchToTextPresentation);
    connect(textEditor, &TextEditor::insertCancelled, this, &UIWidget::switchToTextPresentation);
}

void UIWidget::configureWidgets()
{
}
