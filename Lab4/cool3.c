/* Lab3 Something Cool
 * Lufkin, King, Trusty
 * ECE 477
 * cool3.c
 * reads /proc/uptime to get the time the system has been up and running
 * outputs the time in 8 bit format where each bit corresponds to 10 seconds.
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "gpio.c"

void main()
{
    FILE *fp;
	int x, c, z;
	long int uptime;
	char buff[100];
    const int mask=1;
	
	z = 0;

	//import GPIO pins for use and set to output
	for (x=0; x<8; x++) {
        gpio_export(x);
        usleep(1000000);
        gpio_direction(x,"out");
        usleep(1000000);
    }

	while (z==0) {
		
		//opends /proc/uptime and reads uptime in seconds
		fp = fopen("/proc/uptime", "r");
		if(fp == NULL) {
			printf("export error\n");
			exit(1);
		}
		fscanf(fp, "%s", buff);
		fclose(fp);
		
		//convert input to a long int
	    uptime = strtol(buff, NULL, 0);
		
		//divide the time by 10 for each bit to correspond to 10 sec
		uptime = uptime / 10;	
	    //check if each bit position is a 0 or 1 and set the value accordingly.
	    for (x=0;x<8;x++) {
	        c = (uptime >> x) & mask;
	        if(c) {
	            gpio_value(x,1);
	        } else {
				gpio_value(x,0); 
			}
	    }
		
		//if uptime/10 cannot be displayed within 8 bits
		if (uptime>255) {
			z=1;
		}
		usleep(100000);
	}
    //unexport all used GPIO pins
    for (x=0;x<8;x++) {
        gpio_unexport(x);
    }

}

