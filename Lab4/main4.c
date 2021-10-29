/* ECE 477 Lab 4
 * King Lufkin the Trusty
 * main4.c
 * Interfacing with GPIO outputs and Inputs
 * This program lights one LED at a time from LS to MS with a delay between each 
 * state. This delay starts at 1024 ms and goes down to 32 ms. Each time it doubles or halves 
 * depending on the direction. Button A (GPIO 14) decreases the delay between each
 * blink and Button B (GPIO 15) increases the delay between each blink. If the delay is the lowest 
 * it can go, button A switches the direction the LEDs are blinking. The same is true for button B 
 * if the delay is slow enough. All subroutines are in gpio_func.c while gpio sys file 
 * manipulation functions are in gpio.c  
 */

#include <stdio.h>
#include <string.h>
#include "gpio.c"
#include "gpio_func.c"

int main()
{
	//main setup for lab 4 function located in gpio_func
	export_L4();
	
	//the loop that has the repeating code inside
	L4_loop();
	
	//cleanup
	unexport_L4();	
	return 0; 
}
