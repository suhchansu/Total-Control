#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QUdpSocket>
#include <stdio.h>


class Setting : public QWidget
{
    Q_OBJECT
public:
    explicit Setting(QWidget *parent = 0);

public:
    QPushButton *OK;
    QPushButton *CANCEL;
    QLineEdit *ipEdit,*portEdit;
    QLabel *ipLabel,*portLabel;

    QHBoxLayout * hlayout1,*hlayout2;
    QVBoxLayout * vlayout;

    FILE *setting;

signals:
    
public slots:

    void getipport();

    
};

#endif // SETTING_H
