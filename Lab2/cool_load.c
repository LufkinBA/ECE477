/*Lab 2 something cool
 *cool_load.c
 *Lufkin, King, Trusty
 *This program finds the cpu load of the machine and
 *lights up LEDs hooked up to GPIO ports 0-7 corresponding
 *to the load of the machine over the course of a minute. The
 *code included in gpio.c was originally developed for Andrew
 *Sheaff's Intro to Unix Admin ECE 331 course and modified for 
 *use in this program. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpio.c"

int main()
{
	FILE *zed;
	char buff[100];
	double d;
	int i, x, z;
	
	//export and set to output GPIO ports 0-7
	for (x=0; x<8; x++)	{
		gpio_export(x);
		usleep(1000000);
		gpio_direction(x, "out");
		usleep(1000000);
	}

	z = 0;
	
	//runs this operation 60 times. ~1min
	while (z<60) {
		
		//opens /proc/loadavg and takes the first value to operate on
		zed = fopen("/proc/loadavg", "r");
		if(zed == NULL) {
			printf("export error\n");
			exit(1);
		}
		fscanf(zed, "%s", buff);
		fclose(zed);
		
		sscanf(buff, "%lf",&d);
		printf("%lf\n",d);
	
		//convert the number from a decimal percent value to an int
		i = 9*d;
		i--;		
		
		//makes sure lights that arent lit are off
		for (x=i+1;x<8;x++) {
			gpio_value(x,0);
			usleep(10000);
		}

		//turns on LEDs corresponding to the ratio
		for (x=i;x>=0;x--) {
			gpio_value(x,1);
			usleep(10000);
		}
		//wait 1 sec
		usleep(1000000);
		z++;
	}
	
	//unexport all pins used
	for (x=0;x<8;x++) {
		gpio_unexport(x);
	}
	return 0;
}
