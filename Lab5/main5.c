#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <errno.h>
#include <unistd.h>

// Interupt counters for each button
volatile int rising_edge = 0;

void interrupt_0()
{
    rising_edge++;
}

int main()
{
	//variables
	int x=0, tmp2; 
	int array[60];
	double tmp=0; 
		
	wiringPiSetupGpio();

	pinMode(0, INPUT);
	
	if (wiringPiISR(0, INT_EDGE_FALLING, &interrupt_0) < 0) {
		perror("Error");
		return 1;
	}

	while (x < 60) {
	
		usleep(1000000);
		tmp2 = rising_edge; 

		printf("The falling edge count is: %d \n", tmp2);
		array[x] = tmp2; 
		rising_edge = 0; 
		tmp2 = 0;
		x++;
	}
	
	for (x=0; x<60; x++) {
		tmp = tmp+array[x];
	}
	tmp=tmp/60;

	printf("The average frequency of the AVR output is: %lfHz\n", tmp); 
	
	return 0; 
}

