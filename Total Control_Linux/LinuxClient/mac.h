#ifndef MAC_H
#define MAC_H

#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

class Mac
{
public:
    Mac();
    unsigned char mac_address[6];
};

#endif // MAC_H
