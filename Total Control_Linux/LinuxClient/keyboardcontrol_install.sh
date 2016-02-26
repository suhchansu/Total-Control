#!/bin/sh
gnome-terminal -e "sudo gcc -o keyboardcontrol keyboardcontrol.c"
gnome-terminal -e "sudo chmod 4777 ./keyboardcontrol"
