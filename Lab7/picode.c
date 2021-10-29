#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ROOM_mV .380
#define ROOM_C 21.6
#define SCALE .802


int init(void);

int main(int argc, char * argv[])
{
	FILE *serial_out;
	FILE *serial_in;
	FILE *disk_out=NULL;
	FILE *fp;
	float temp, mV;
	int fdserial;
	int len;
	char buffer[100];
	char conv[100];

	fp = fopen("templogs.txt", "w+"); 
	if (fp == NULL) {
		printf("Unable to create file for writing");
		return -1; 
	}
	
	fdserial=init();
	if(fdserial <1) exit(0);
	serial_out=fdopen(fdserial,"w");	
	serial_in=fdopen(fdserial,"r");
	if(serial_out==NULL || serial_in==NULL) printf("fdopen failed \n"),exit(0);
	if(argc>1) disk_out=fopen(argv[1],"w");
	if(disk_out==NULL) disk_out=stdout;
   
	fprintf(serial_out,"Start\n");
	while(fgets(buffer,100,serial_in)) {
		len = strlen(buffer);
		if( buffer[len-1] == '\n' )
			buffer[len-1] = 0;
		mV = atoi(buffer);
		mV = (mV * 1.1) / 1024;
		temp = (((mV - ROOM_mV) * 1000) *SCALE) + ROOM_C;
		snprintf(conv, 32, "%s,%lf,%lf\n",buffer,mV,temp);
		fputs(conv,disk_out);
		fputs(conv,fp);
		sleep(1);
	}
}
   




int  init()
  {
    int fd1;
    struct termios tc;                // terminal control structure

    //todo serial port should not be hard coded
    fd1 = open("/dev/serial0", O_RDWR|O_NOCTTY);
    if(fd1<1) 
    {
	    printf("Failed to open serial port\n");
	    return 0;
    }
    tcgetattr(fd1, &tc);
    tc.c_iflag = IGNPAR;
    tc.c_oflag = 0;
    tc.c_cflag = CS8 | CREAD | CLOCAL; //8 bit chars enable receiver no modem status lines
    tc.c_lflag = ICANON;

    //todo baud rate should not be hard coded
    cfsetispeed(&tc, B9600);
    cfsetospeed(&tc, B9600);
    //todo should have bits per character set
    tcsetattr(fd1, TCSANOW, &tc);
  return fd1;
 }

