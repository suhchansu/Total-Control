#include "connectbutton.h"

ConnectButton::ConnectButton(char *name,QWidget *parent):QPushButton(name)
{
    this->parent = parent;
    udp=new Socket();
    QObject::connect(this,SIGNAL(clicked()),this,SLOT(connectting()));
}


void ConnectButton::connectting()
{
    udp->connecting();
    parent->hide();
}
