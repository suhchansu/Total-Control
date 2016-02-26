#!/bin/sh
gnome-terminal -e "sudo gcc -o mousecontrol mousecontrol.c"
gnome-terminal -e "sudo chmod 4777 ./mousecontrol"
