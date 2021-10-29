/* Lab 2 LED Control with GPIO on RPi
 * Lufkin, King, Trusty
 * ECE 477
 * Creates an arpeggio of the lights turning on and off.
 * Small light show just to play around with the LEDs
 * for_fun.c
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "gpio.c"

void main(int argc,char *argv[])
{
    int x, y;
	char arpeg[8][3] ={"do","re","mi", "fa", "so", "la", "ti", "do"};
    
	//import GPIO pins 0-7 for use and set to output
    for (x=0; x<8; x++) {
        gpio_export(x);
        usleep(1000000);
        gpio_direction(x,"out");
        usleep(1000000);
    }
	
	printf("Ahem\n");
    //going up
	for (x=0;x<8;x++) {
		printf("%s\n", arpeg[x]);
        gpio_value(x,1);
		sleep (1);
		gpio_value(x,0);
	}
	
	//going down
	for (x=7;x>=0;x--) {
		printf("%s\n", arpeg[x]);
        gpio_value(x,1);
		sleep (1);
		gpio_value(x,0);
	}

	printf("Lets have some fun shall we?\n");
	//turns on 0,2,4,6 then turns on 1,3,5,7 and alternates 10 times
	for (x=0;x<10;x++) {
		for(y=0;y<2;y++) {
			gpio_value(y,1);
			gpio_value((y+2),1);
			gpio_value((y+4),1);
			gpio_value((y+6),1);
			usleep(500000);
			gpio_value(y,0);
			gpio_value((y+2),0);
			gpio_value((y+4),0);
			gpio_value((y+6),0);
		}
	}	
	
	
    //wait 5 seconds
    usleep(5000000);

    //turn all the LEDs off
    for (x=0;x<8;x++) {
        gpio_value(x,0);
    }

    //unexport all used GPIO pins
    for (x=0;x<8;x++) {
        gpio_unexport(x);
    }
}

