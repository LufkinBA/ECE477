/* King Lufkin the Trusty
 * ECE 477 - Lab 3
 * LED Control w/ RPi GPIO pins.
 */

#include <stdio.h>
#include "gpio.c"

int main(void)
{
        FILE *fp;
        char buffer[5];
        double load;
        int i;
        double limits[8] = {0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 2, 4};

        //export and set to output GPIO ports 0-7
        for (i = 0; i < 8; i++) {
                gpio_export(i);
                usleep(1000000);
                gpio_direction(i, "out");
                usleep(1000000);
        }


        while (1) {

                //opens /proc/loadavg and takes the first value to operate on
                fp = fopen("/proc/loadavg", "r");
                if(fp == NULL) {
                        printf("export error\n");
                        exit(1);
                }
                fscanf(fp, "%s", buffer);
                fclose(fp);

                sscanf(buffer, "%lf", &load);
                printf("%lf\n", load);

                for (i = 0; i < 8; i++) {
                        if (load >= limits[i])
                                gpio_value(i, 1);
                        else
                                gpio_value(i, 0);
                }
				i = gpio_read(0);
				printf("%i\n",i);

                //wait 1 sec
                usleep(1000000);
                //seconds++;
        }
}

