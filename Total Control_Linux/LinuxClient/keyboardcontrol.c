
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
	struct input_event click_event, event_end;
	int click;


	int fd = open("/dev/input/event3",O_RDWR);



	if(!fd)
	{
		printf("Error open mouse : %s \n",strerror(errno));
		return -1;
	}


	click=atoi(argv[1]);



	 //left pull
	
	gettimeofday(&click_event.time,NULL);
	click_event.type = EV_KEY;
	click_event.code = click;
	click_event.value = atoi(argv[2]);
	
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
