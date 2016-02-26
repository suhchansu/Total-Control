#include "setting.h"
#include <fcntl.h>
Setting::Setting(QWidget *parent) :
    QWidget(parent)
{
    OK=new QPushButton("OK");
    CANCEL=new QPushButton("CANCEL");
    hlayout1=new QHBoxLayout();
    hlayout2=new QHBoxLayout();
    vlayout=new QVBoxLayout();
    ipEdit= new QLineEdit();
    portEdit = new QLineEdit();
    ipLabel = new QLabel("IP");
    portLabel = new QLabel("PORT");

    connect(OK,SIGNAL(clicked()),this,SLOT(getipport()));

    hlayout1->addWidget(ipLabel);
    hlayout1->addWidget(ipEdit);
    hlayout1->addWidget(OK);

    hlayout2->addWidget(portLabel);
    hlayout2->addWidget(portEdit);
    hlayout2->addWidget(CANCEL);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    this->setLayout(vlayout);
    this->setWindowTitle("Total Control v1.0");
}


void Setting::getipport()
{

    QString port;
    QString ip;
    setting=fopen("settingIO.txt","wt");
    ip=ipEdit->text();
    port=portEdit->text();

    char *charip;
    char *charport;
    QByteArray ba;

    ba=ip.toLatin1();
    charip=ba.data();

    fprintf(setting,"%s\n",charip);

    ba=port.toLatin1();
    charport=ba.data();

    fprintf(setting,"%s\n",charport);

    fclose(setting);

    this->close();

}
