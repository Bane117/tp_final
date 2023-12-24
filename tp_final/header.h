#ifndef __header__
#define __header__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <pcf8591.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#include <fcntl.h> 
#include <unistd.h> 



void remote();
void send();
void receive();
int updatedspeed(); 



//int led [8] = {26,21,20,16,12,25,24,23};
//int speed;


#endif
