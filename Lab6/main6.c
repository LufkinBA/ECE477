/* ECE 477 Lab 6
 * King Lufkin the Trusty
 * Setting up serial communication through USART 
 * from the Raspberry Pi side. 
 * The routine sends the string "START" to the AVR
 * prompting the AVR to measure the input voltage from the power rail.
 * The onboard ADC in the AVR makes the conversion and sends a 10bit number back
 * to the RPi. The RPi then makes the conversion back to a voltage reading
 * and displays that on the screen.
 */

/* Useful information:
 * GPIO 14 is UART0_TXD i.e. transmission line
 * GPIO 15 is UART0_RXD i.e. reception line
 * ADC = (Vin * 1024)/Vref where Vin is "always" 1.1V. Solving for Vref
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
// void setup_stdout(void); //todo maybe?

int main()
{
	int x, fd;
	char a,buf[1000];

	if (setup_stdin() == 1) return 1;
	
	fd = init();
	
	if (fd == NULL) return 1;
	
	printf("Please type START and press Enter\n");
	
	//code recieved from Bruce Segee	
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

	//serial0 defaults to primary UART Transmission line on all RPi systems
    fd1 = open("/dev/serial0", O_RDWR|O_NOCTTY);  
    if (fd1 == NULL) {
		printf("Couldn't open serial port\n");	
		return NULL; 
	}
	
	//Code recieved from Bruce Segee
	tcgetattr(fd1, &tc);
    tc.c_iflag = IGNPAR;
    tc.c_oflag = 0;
    tc.c_cflag = CS8 | CREAD | CLOCAL; //8 bit chars enable receiver no modem status lines
    tc.c_lflag =0 ;

	//Set input and output to 9600 baud rate
    cfsetispeed(&tc, B9600);
    cfsetospeed(&tc, B9600);
    tcsetattr(fd1, TCSANOW, &tc);
	
	return fd1;
}

