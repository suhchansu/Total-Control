#ifndef CLICK_H
#define CLICK_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
class Click
{
public:
    Click();

    int clickMethod(int click);
};

#endif // CLICK_H
