// ECE 477
// Tues. 2/23
// "Fork"

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "math.h"

int main(void)
{
        int x;

        double z;

        for(x=0;x<10;x++) {
                if(fork())
                        printf("stuff\n");
                else
                        printf("things\n");

                z=x*x;
                z=sin(z);
                printf("and\n");
        }
        return 0;
}
