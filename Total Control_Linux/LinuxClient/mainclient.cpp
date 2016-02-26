#include "mainclient.h"
#include "connectbutton.h"

MainClient::MainClient(QWidget *parent) :
    QWidget(parent)
{

    Setting *setting =new Setting();
    QSystemTrayIcon *systray=new QSystemTrayIcon();
    ConnectButton *button = new ConnectButton("connect",this);
    QPushButton *connectButton2 = new QPushButton("Disconnect");
    QPushButton *connectButton3 = new QPushButton("Setting");
    QMenu *traymenu =new QMenu();

    QAction *minimizeAction= new QAction(("Mi&nimize"), this);
    QAction *restoreAction = new QAction(("&Restore"), this);
    QAction *quitAction = new QAction(("&Quit"), this);
    QAction *connectAction = new QAction(("&Connect"),this);
    QAction *disconnectAction = new QAction(("&Disconnect"),this);

    QObject::connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    QObject::connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    QObject::connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    traymenu->addAction(connectAction);
    traymenu->addAction(disconnectAction);
    traymenu->addSeparator();
    traymenu->addAction(minimizeAction);
    traymenu->addAction(restoreAction);
    traymenu->addSeparator();
    traymenu->addAction(quitAction);


    systray->setContextMenu(traymenu);


    systray->setIcon(QIcon("./123.png"));
    QObject::connect(connectButton2,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(connectButton3,SIGNAL(clicked()),setting,SLOT(show()));
    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(button);
    layout->addWidget(connectButton2);
    layout->addWidget(connectButton3);
    this->setLayout(layout);

    this->setWindowTitle("Total Control v1.0");
    systray->setVisible(true);

}
