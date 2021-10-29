/* Lab3 Something Cool
 * Lufkin, King, Trusty
 * ECE 477
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "gpio.c"

void main(int argc,char *argv[])
{
    FILE *fp;
	int x, c, z;
	long int uptime;
	char buff[100];
    const int mask=1;
	
	z = 0;
	while (z==0) {
	
		fp = fopen("/proc/uptime", "r");
		if(fp == NULL) {
			printf("export error\n");
			exit(1);
		}
		fscanf(fp, "%s", buff);
		fclose(fp);
		
		//convert input to a long int
	    uptime = strtol(buff, NULL, 0);
	    
		//import GPIO pins for use and set to output
	    for (x=0; x<8; x++) {
	        gpio_export(x);
	        usleep(1000000);
	        gpio_direction(x,"out");
	        usleep(1000000);
	    }
	
	    //check if each bit position is a 0 or 1 and set the value accordingly.
	    for (x=0;x<8;x++) {
	        c = (uptime >> x) & mask;
	        if(c) {
	            gpio_value(x,1);
	        }
	    }
	
		if (uptime>255) {
			z=1;
		}
		usleep(1000000);
	}
    //unexport all used GPIO pins
    for (x=0;x<8;x++) {
        gpio_unexport(x);
    }

}

