/* ECE 477 Final Project 
 * King Lufkin the Trusty
 * rpi.c
 * The function of this project was to make a basic waveform generator
 * that is capable of at least 3 different frequencies and be able to 
 * create a sine wave, a triangle wave, a sawtooth wave, and a square wave.
 * The square wave function will also have the ability to change the duty cycle  
 * in real time. A Raspberry Pi will communicate with an ATMEGA88pa (AVR) through
 * UART and the ATMEGA will use Timer generated interrupts to get a proper, smooth
 * output. The ATMEGA has a resistor ladder based parallel input DAC that 
 * will output the generated wave as an analog signal. 
 */


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
    char a;

	// Initialization and error checking
    if (setup_stdin() == 1) return 1;

    fd = init();

    if (fd == NULL) return 1;

	// Prompt the user
    printf("Welcome to the Waveform generator program\n");
	printf("Here are the commands you can use to control the program\n");
	printf("For 500Hz signal, press 'L'\n");
	printf("For 1kHz signal, press 'M'\n");
	printf("For 5kHz signal, press 'H'\n");
	printf("For a sine wave, press 'S'\n");
	printf("For a triangle wave, press 'T'\n");
	printf("For a sawtooth wave, press 'W'\n");
	printf("For a square wave, press 'Q'\n");
	printf("Type 'B' to begin the output of the selected wave and frequency\n");
	printf(" and type 'P' to stop.\n");

    // Infinitely listen and recieve from the UART
	// Code recieved from Bruce Segee    
    if (fork()){
        from_to(fd,1);
    }else{
        from_to(0,fd);
    }

    return 0;
}

//Sets up the termios struct with special flags. 
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

//Code recievd from Bruce Segee
char from_to(int f1, int f2)
{
    char c;
    while(1) {
		//printf("%d %c %d\n", f1, c, f2);
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

    //Set input and output to 2400 baud rate
    cfsetispeed(&tc, B2400);
    cfsetospeed(&tc, B2400);
    tcsetattr(fd1, TCSANOW, &tc);

    return fd1;
}

 
