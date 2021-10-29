#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//exports gpio 0-7 and sets to output also exports GPIO 14 and 15 
//as input
void export_L4(void);

//contains while loop for LED blinking and button reading
void L4_loop(void);

//unexports GPIO 0-7, 14, and 15
void unexport_L4(void);

