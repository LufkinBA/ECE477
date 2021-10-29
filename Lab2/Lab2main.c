/* Lab 2 LED Control with GPIO on RPi
 * Lab2main.c
 * Lufkin, King, Trusty
 * ECE 477
 * Program takes a single argument from the command line which could be in decimal, octal, or hex.
 * The inputted 8 bit number corresponds to which of the 8 LEDs is on. Uses GPIO ports 0-7.
 * For example. 0xff as an input would turn on all 8 LEDs. Code uses gpio.h which was designed 
 * and constructed by Blake Lufkin for Andrew Sheaff's Intro to Administration with Unix course 
 * and was modified for use in this program.
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "gpio.c"

void main(int argc,char *argv[])
{
    int u_in, x, c;
    const int mask=1;

	//check for input on the command line
	if (argv[1] == NULL) {
		printf("No command line argument detected\n");
		exit(1);
	}
	
	//convert input to a long int
    u_in = strtol(argv[1], NULL, 0);

    //value checking
	if (u_in > 256 || u_in < 0) {
        printf("Invalid Input. Input must be between 0 and 256\n");
        exit(1);
    }

    //import GPIO pins for use and set to output
    for (x=0; x<8; x++) {
        gpio_export(x);
        usleep(1000000);
        gpio_direction(x,"out");
        usleep(1000000);
    }

    //check if each bit position is a 0 or 1 and set the value accordingly.
    for (x=0;x<8;x++) {
        c = (u_in >> x) & mask;
        if(c) {
            gpio_value(x,1);
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

