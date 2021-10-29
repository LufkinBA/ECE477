/* ECE 477 Lab 6
 * King Lufkin the Trusty
 * Something Cool i.e. Part B
 * Establishes a UART connection between A RPi4 and an
 * ATMEGA88PA. The user is to input any character, special character,
 * or number and the AVR returns the character and its ASCII value.
 */

/* Useful information:
 * GPIO 14 is UART0_TXD i.e. transmission line
 * GPIO 15 is UART0_RXD i.e. reception line
 */

//Standard File Descriptors 0: stdin, 1: stdout, 2: stderr

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int init();
char from_to(int, int);
int setup_stdin(void);

int main()
{
	int x, fd;
	char a,buf[1000];

	if (setup_stdin() == 1) return 1;
	
	fd = init();
	
	if (fd == NULL) return 1;
	
	printf("Please enter any value on the keyboard and the AVR will determine its ASCII value\n");
	
	if (fork()){
		from_to(fd,1);
	}else{
		from_to(0,fd);
	}
	return 0;
}


int setup_stdin(void)
{
	struct termios tc;
	
	/* take a file handle and obtain the terminal attributes associated 
	 * with that file descriptor, 0 is stdin
	 */
	if (tcgetattr(0, &tc) != 0) { 
		printf("tcgetattr error\n");
		return 1; 
	}
	
	//no canonical mode, echo
	tc.c_lflag &=~ICANON;
	tc.c_lflag |= ECHO;
	
	//set changes to take effect now
	if (tcsetattr(0, TCSANOW, &tc) != 0) {
		printf("tcsetattr error\n");
		return 1; 
	}
		
	return 0; 	
}


char from_to(int f1, int f2)
{  
	char c;
	while(1) {
		if(read(f1,&c,1)) {
			write(f2,&c,1);
		}  
	}
	return c;
}

//Initializes serial port UART0
int init()
{
    int fd1;
    struct termios tc;                // terminal control structure

    fd1 = open("/dev/serial0", O_RDWR|O_NOCTTY);  
    if (fd1 == NULL) {
		printf("Couldn't open serial port\n");	
		return NULL; 
	}
	
	tcgetattr(fd1, &tc);
    tc.c_iflag = IGNPAR;
    tc.c_oflag = 0;
    tc.c_cflag = CS8 | CREAD | CLOCAL; //8 bit chars enable receiver no modem status lines
    tc.c_lflag =0 ;

    cfsetispeed(&tc, B9600);
    cfsetospeed(&tc, B9600);
    tcsetattr(fd1, TCSANOW, &tc);
	
	return fd1;
}

