
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
	struct input_event eventx, eventy, click_event, event_end;
	int i,click;


	int fd = open("/dev/input/event14",O_RDWR);



	if(!fd)
	{
		printf("Error open mouse : %s \n",strerror(errno));
		return -1;
	}


	click=atoi(argv[1]);

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
		case 41:
			gettimeofday(&click_event.time,NULL);
			click_event.type = EV_REL;
			click_event.code = REL_WHEEL;
			click_event.value=atoi(argv[2]);
			break;
	}
	if(click!=0)
	{
	gettimeofday(&event_end.time,NULL);
	event_end.type = EV_SYN;
	event_end.code = SYN_REPORT;
	event_end.value = 0;
	
			
			write(fd,&click_event,sizeof(click_event));
			write(fd,&event_end,sizeof(event_end));
			printf("success");
	}

	close(fd);
	return 0;
}
