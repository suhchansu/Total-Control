#include "mouseinput.h"

mouseinput::mouseinput()
{
}

void mouseinput::SendCommand(int x,int y, int value)
{
    struct input_event eventx, eventy, click_event, event_end;
        int click;


        int fd = open("/dev/input/event3",O_RDWR);

        if(!fd)
        {
            printf("Error open mouse : %s \n",strerror(errno));
        }

        memset(&eventx,0,sizeof(eventx));
        memset(&eventy,0,sizeof(eventy));
        memset(&event_end,0,sizeof(event_end));


        gettimeofday(&eventx.time,NULL);
        eventx.type = EV_REL;
        eventx.code = REL_X;
        eventx.value = x;  //x

        gettimeofday(&eventy.time,NULL);
        eventy.type = EV_REL;
        eventy.code = REL_Y;
        eventy.value = y;  //y

        click=value;

        switch(click)
        {
            case 11:   //left push

                gettimeofday(&click_event.time,NULL);
                click_event.type = EV_KEY;
                click_event.code = BTN_LEFT;
                click_event.value = 1;
                break;

            case 10:  //left pull

                gettimeofday(&click_event.time,NULL);
                click_event.type = EV_KEY;
                click_event.code = BTN_LEFT;
                click_event.value = 0;
                break;
            case 21:  //right

                gettimeofday(&click_event.time,NULL);
                click_event.type = EV_KEY;
                click_event.code = BTN_RIGHT;
                click_event.value = 1;
                break;
            case 20:

                gettimeofday(&click_event.time,NULL);
                click_event.type = EV_KEY;
                click_event.code = BTN_RIGHT;
                click_event.value = 0;
                break;
        }
        gettimeofday(&event_end.time,NULL);
        event_end.type = EV_SYN;
        event_end.code = SYN_REPORT;
        event_end.value = 0;
        if(value!=0)
        {
                write(fd,&eventx,sizeof(eventx));
                write(fd,&eventy,sizeof(eventy));
                write(fd,&click_event,sizeof(click_event));
                write(fd,&event_end,sizeof(event_end));
        }

        close(fd);
}
