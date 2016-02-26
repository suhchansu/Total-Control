#ifndef MAINCLIENT_H
#define MAINCLIENT_H

#include <QWidget>

#include <QPushButton>
#include <QHBoxLayout>
#include <QIcon>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QUdpSocket>
#include "mac.h"
#include "setting.h"
#include <stdio.h>

class MainClient : public QWidget
{
    Q_OBJECT
public:
    explicit MainClient(QWidget *parent = 0);

    FILE *settingIO;
    QUdpSocket *upd;
    QHostAddress sendIp;
    QString transIp_from_charIp;
    char message[50];  //MAC Address
    int sendport;
    unsigned char mac_address[6];
    Mac mac;  //맥주소 만드는 클래스(생성자가 맥주소를 16진수변환해서 unsigned char로 만들어놓습니다)


    
signals:
    
public slots:
};

#endif // MAINCLIENT_H
