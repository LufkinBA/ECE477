/* ECE 477 Lab 4
 * King Lufkin the Trusty
 * Interfacing with GPIO outputs and Inputs
 * This program lights one LED at a time from LS to MS with a delay between each 
 * state. This delay starts at 
 */

#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <errno.h>
#include <unistd.h>

// Interupt counters for each button
volatile int fifteen = 0;
volatile int fourteen = 0;

void interrupt_15()
{
	fifteen++;
}


void interrupt_14()
{
	fourteen++;
}

int main()
{
	int bc,x, i, z, direc;	
	int delay[6] = {32, 16, 8, 4, 2, 1};
	
	/* Set up wiringPi */
	wiringPiSetupGpio();
	
	//set pins 0-7 to outputs
	for (i = 0; i < 8; i++) {
	pinMode(i, OUTPUT);
	}
	
	//set GPIO 14 and 15 to input	
	pinMode(14, INPUT);
	pinMode(15, INPUT);
	
	//counter,direction and break values set
	z = 0;
	i = 0; 
	direc = 0; //0 means forward(0-7), 1 means backward(7-0)
	bc = 0;
	
	// Interupt for buttons, falling edge
	if (wiringPiISR(14, INT_EDGE_FALLING, &interrupt_14) < 0) {
		perror("Error");
		return 1;
	}	
		
	if (wiringPiISR(15, INT_EDGE_FALLING, &interrupt_15) < 0) {
		perror("Error");
		return 1;
	}
	
	//main function that blinks and stuff
	while (1) { 
		digitalWrite(i,1);
		
		for(x=0;x<delay[z];x++) {
			usleep(32000);

			//deciding direction and rate of LEDs	
			if (fourteen  >= 1 || fifteen >= 1) {
				if (fourteen >= 1 && fifteen >= 1)
					bc = 1; 
				if (fourteen >= 1){
					if (z==0) {
						direc = direc ^ 1;
					} else {
						z--; 
					}
				}
				if (fifteen >= 1) {
					if (z==5) {
						direc = direc ^ 1; 
					} else {
						z++; 
					}
				} 
			}
			// Reset interrupt counters after each loop pass
			fourteen = 0;
			fifteen = 0;
		}
		//delay the correct amount of time based on the value of the array. 	
		digitalWrite(i,0);
		if (bc == 1)
			break;
		
		//increments or decrements based on the direc value
		if (direc == 0){
			i++;
			if (i>7)
				i=0;
		} else {
			i--;
			if (i<0)
				i=7;
		}
	}
	return 0; 
}
