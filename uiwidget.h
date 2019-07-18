#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

class UIWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UIWidget(QWidget *parent = nullptr);
    ~UIWidget();

signals:
    void queryData(QString query);

private slots:
    void clicked();

private:
    QPushButton *queryButton;
    QLineEdit *queryLine;
    QHBoxLayout *boxLayout;

    void makeConnections();
    void configureWidgets();
};


#endif // UIWIDGET_H
