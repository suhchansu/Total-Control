#ifndef CONNECTBUTTON_H
#define CONNECTBUTTON_H

#include <QPushButton>
#include <socket.h>

class ConnectButton : public QPushButton
{
    Q_OBJECT
public:
    ConnectButton(char *name,QWidget *parent);
    Socket *udp;
    QWidget *parent;

public slots:
    void connectting();

};

#endif // CONNECTBUTTON_H
