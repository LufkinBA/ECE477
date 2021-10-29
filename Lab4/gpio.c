//Blake Lufkin
//gpio.c
//File containing functions for manipulating gpio ports
//Last updated: 3/2/2020
#include "gpio.h"

int gpio_export(int pin)
{
	FILE *fp;
	char c[2];
	sprintf(c, "%d", pin);

	//opens the export file
	fp = fopen("/sys/class/gpio/export", "w+");
	if (fp == NULL) {
		printf("export error");
		return 1;
	}

	//writes the selected pin in export file
	fwrite(c, sizeof(c), 1, fp);
	//export makes a new directory for gpioN where N is pin
	fclose(fp);
	return 0;
}

int gpio_unexport(int pin)
{
	FILE *fp;
	char c[2];
	sprintf(c, "%d", pin);

	//opens the unexport sys file as writeonly
	fp = fopen("/sys/class/gpio/unexport", "w+");
	if (fp == NULL) {
		printf("unexport error");
		return 1;
	}

	//writes the selected pin in unexport file
	fwrite(c, sizeof(c), 1, fp);
	//unexport deletes the directory gpioN where N is pin
	fclose(fp);
	return 0;
}

/*Changes the GPIO pin selected to either "out" for output
 * or "in" for input. Main use is to change the pin to output
 * a signal or change the file content to "out"
 */
int gpio_direction(int pin, char *str)
{
	FILE *fp;

	//Creating proper path using inputed GPIO pin
	char c[12];
	sprintf(c, "%d/direction", pin);
	char path[] = "/sys/class/gpio/gpio";
	strcat(path, c);

	fp = fopen(path, "w");
	if (fp == NULL) {
		printf("direction error\n");
		return 1;
	}

	fwrite(str, sizeof(str), 1, fp);
	fclose(fp);
	return 0;
}

/*Changes the value of the selected gpio pin file
 *Where 1 means turn on and 0 means turn off
 */
int gpio_value(int pin, int value)
{
	FILE *fp;
	char v[1];
	//Creating proper path using inputed GPIO pin
	char c[8];
	sprintf(c, "%d/value", pin);
	char path[] = "/sys/class/gpio/gpio";
	strcat(path, c);

	fp = fopen(path, "w");
	if (fp == NULL) {
		printf("value error\n");
		return 1;
	}
	sprintf(v, "%d", value);
	fwrite(v, sizeof(v), 1, fp);
	fclose(fp);
	return 0;
}

int gpio_read(int pin)
{
	FILE *fp;
	char buffer[1];
	char v[1];
	//Creating proper path using inputed GPIO pin
	char c[8];
	sprintf(c, "%d/value", pin);
	char path[] = "/sys/class/gpio/gpio";
	strcat(path, c);

	fp = fopen(path, "r");
	if (fp == NULL) {
		printf("read error\n");
		return 1;
	}
	
	fscanf(fp, "%s", buffer);
	fclose(fp);
	
	return atoi(buffer);
}
