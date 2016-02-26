#include "keyboardinput.h"

keyboardinput::keyboardinput()
{
}


void keyboardinput::SendCommand(int scancode, int value)
{

    struct input_event event, event_end;


        int fd = open("/dev/input/event2",O_RDWR);

        if(!fd)
        {
            printf("Error open mouse : %s \n",strerror(errno));
        }

        memset(&event,0,sizeof(event));
        memset(&event,0,sizeof(event_end));

        gettimeofday(&event.time,NULL);
        event.type = EV_KEY;
        event.code = scancode;
        event.value = value;

        gettimeofday(&event_end.time,NULL);
        event_end.type = EV_SYN;
        event_end.code = SYN_REPORT;
        event_end.value = 0;

        write(fd,&event,sizeof(event));
        write(fd,&event_end,sizeof(event_end));

        close(fd);
}
