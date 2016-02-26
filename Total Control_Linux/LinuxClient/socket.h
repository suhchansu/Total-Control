#ifndef SOCKET_H
#define SOCKET_H

#include <QUdpSocket>
#include "mac.h"
#include "click.h"
#include <QCursor>
#include <QDesktopWidget>


#include <stdio.h>

class Socket : public QUdpSocket
{
    Q_OBJECT
public:


    QDesktopWidget *desktop;
    Socket();
    FILE *settingIO;
    QHostAddress sendIp;
    QString transIp_from_charIp;
    char message[50];  //MAC Address
    int sendport;
    unsigned char mac_address[6];
    Mac mac;  //맥주소 만드는 클래스(생성자가 맥주소를 16진수변환해서 unsigned char로 만들어놓습니다)
    Click click;
    QCursor *cursor;

    int x;
    int y;

    int i;
    char *tx,*ty,*tc;
    int calx,caly,calc;

    void connecting();

    int clickMethod(int click);

public slots:
    void reading();
};

#endif // SOCKET_H
