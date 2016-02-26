#include "socket.h"

Socket::Socket()
{
    desktop = new QDesktopWidget();
    x=desktop->screenGeometry().width();
    y=desktop->screenGeometry().height();
    //y=x=800;
    this->bind(7898,this->ShareAddress);
    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(reading()));
    cursor = new QCursor();
}


void Socket::connecting()
{
    settingIO=fopen("settingIO.txt","rt");
    char *charIp=(char*)malloc(sizeof(char)*17);
    fscanf(settingIO,"%s",charIp);
    transIp_from_charIp.append(charIp);
    sendIp.setAddress(transIp_from_charIp);
    fscanf(settingIO,"%d",&sendport);
    char* pcName= getenv("USER");
    int i=0;
    for(pcName;*pcName!='\0';pcName++)
    {
        message[i]=*pcName;
        i++;
    }
    message[i++]='_';
    int end=i+12;
    int j=0;
    for(i;i<end;i++)
    {
        message[i++]=mac.mac_address[j]/10;
        message[i]=mac.mac_address[j++]%10;
    }
    message[i++]='_';
    message[i++]=x/100;
    message[i++]=x%100;
    message[i++]='_';
    message[i++]=y/100;
    message[i++]=y%100;
    message[i]='_';
    this->writeDatagram(message,sizeof(message),sendIp,sendport);
    transIp_from_charIp.clear();
    fclose(settingIO);


}


void Socket::reading()
{
    char copymessage;
    while(/*upd->hasPendingDatagrams()*/ this->hasPendingDatagrams())
    {
        char message[106];
        this->readDatagram(message,sizeof(message));

        copymessage=message[0];


        if(copymessage=='0')
        {
            strtok(message," ");
            tx=strtok(NULL," ");
            ty=strtok(NULL," ");
            tc=strtok(NULL," ");
            calx=atoi(tx);
            caly=atoi(ty);
            calc=atoi(tc);
            cursor->setPos(calx,caly);  //마우스이동
            if(calc!=0)
            {
                QString str="./mousecontrol ";
                QString copystr=str;
                if(calc==1)
                {
                    copystr.append("11");
                    system(copystr.toStdString().c_str());
                    copystr=str;
                    copystr.append("10");
                    system(copystr.toStdString().c_str());

                }
                else if(calc==2)
                {
                    copystr.append("21");
                    system(copystr.toStdString().c_str());
                    copystr=str;
                    copystr.append("20");
                    system(copystr.toStdString().c_str());
                }
                else if(calc==4)
                {
                    copystr.append("41 ");
                    copystr.append(tx);
                    system(copystr.toStdString().c_str());
                }
            }

         }
        else if(copymessage=='1')
        {
            strtok(message," ");
            tx=strtok(NULL," ");
            ty=strtok(NULL," ");
            tc=strtok(NULL," ");
            calx=atoi(tx);
            caly=atoi(ty);
            calc=atoi(tc);
                QString str="./keyboardcontrol ";
                QString copystr=str;
                    if(caly==1)
                    {
                        copystr.append(tx);
                        copystr.append(" 1");
                        system(copystr.toStdString().c_str());
                    }
                    else if(caly==0)
                    {
                        if((2<=calx && calx<=14) || (16<=calx && calx<=27) || (30<=calx && calx<=40) || calx==41 || (44<=calx && calx<=52) )
                        {
                            copystr.append(tx);
                            copystr.append(" 1");
                            system(copystr.toStdString().c_str());
                            copystr=str;
                            copystr.append(tx);
                            copystr.append(" 0");
                            system(copystr.toStdString().c_str());

                        }
                        else
                        {
                            copystr.append(tx);
                            copystr.append(" 0");
                            system(copystr.toStdString().c_str());
                        }
                    }
        }


    }
}

