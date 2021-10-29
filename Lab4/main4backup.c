/* ECE 477 Lab 4
 * King Lufkin the Trusty
 * Interfacing with GPIO outputs and Inputs
 * This program lights one LED at a time from LS to MS with a delay between each 
 * state. This delay starts at 1024 ms and goes down to 32 ms. Each time it doubles or halves 
 * depending on the direction. Button A (GPIO 14) decreases the delay between each
 * blink and Button B (GPIO 15) increases the delay between each blink. If the delay is the lowest 
 * it can go, button A switches the direction the LEDs are blinking. The same is true for button B 
 * if the delay is slow enough.  
 */

#include <stdio.h>
#include <string.h>
#include "gpio.c"
#include "gpio_func.c"

int main()
{
	int bc,x, i, As, Ae, Bs, Be, button_push_A, button_push_B, z, direc;	
	int delay[6] = {32, 16, 8, 4, 2, 1}; //the result of desired delay/32
	
	//Export all used gpio pins and set them to either input or output
	export_L4();
	
	//initializing variables and counters 
	z = 0;
	i = 0; 
	direc = 0; //0 means forward(0-7), 1 means backward(7-0)
	bc = 0;
	button_push_A = 0;
	button_push_B = 0;
	
	//main code that performs the LED blinking
	while (1) { 
		
		//turn GPIO i on
		gpio_value(i,1);
		
		//delay 32ms delay[z] times
		for(x=0;x<delay[z];x++) {
			As = gpio_read(14); //button A before delay
			Bs = gpio_read(15); //button B before delay
			usleep(32000);
			Ae = gpio_read(14); //button A after delay
			Be = gpio_read(15); //button B after delay
			
			/*Logic here is based on the button having 4 possible states:	
			 * Button pushed, Button released, Button not pushed, and 
			 * Button held. If it is pushed, perfrom the logic that decides
			 * direction and rate(button_push = 1), if it is held button_push=2
			 * thus do nothing, if the button is released, set button_push=0; 
			 */
			if (As ==1 && Ae == 0)
				button_push_A = 1;
			if ((As == 0 && Ae == 0) && button_push_A == 1)
				button_push_A = 2;
			if (As==0 && Ae == 1)
				button_push_A = 0;
 
			if (Bs ==1 && Be == 0)
				button_push_B = 1;
			if ((Bs == 0 && Be == 0) && button_push_B == 1)
				button_push_B = 2;
			if (Bs==0 && Be == 1)
				button_push_B = 0;

			//debouncing goes here if nessecary
		
		
			//deciding direction and rate of LEDs	
			if (button_push_A == 1 || button_push_B == 1) {
				if (button_push_A==1 && button_push_B==1)
					bc = 1; 
				if (button_push_A==1){
					if (z==0) {
						direc = direc ^ 1;
					} else {
						z--; 
					}
				}
				if (button_push_B==1) {
					if (z==5) {
						direc = direc ^ 1; 
					} else {
						z++; 
					}
				} 
			}
		}
		//delay the correct amount of time based on the value of the array. 	
		gpio_value(i,0);
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
	
	//cleanup 
	//unexport all pins used
	for (i=0;i<8;i++) {
		gpio_unexport(i);
	}
	gpio_unexport(14);
	gpio_unexport(15);
	
	return 0; 
}
