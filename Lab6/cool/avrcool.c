/* Lab 6 
 * King Lufkin the Trusty
 * avrinit.c
 * The AVR program that sets up a UART connection with a Raspberry Pi
 * in order to take in a character and determine its ASCII value and send that 
 * value back to the users terminal. 
 */
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <avr/sleep.h>
#include <string.h>
#include <util/delay.h>
/* USART PINS are as follows:
 * RXD -> PD0 is the Reciever
 * TXD -> PD1 is the Transmitter
 * XCK -> PD4 is the Clock Generator 
 */

/* The functions below are based off of 
 * readtemperature.c code from Bruce Segee:
 * serial_putchar, serial_getchar, serial_stream
 */
void USART_Init(void); 

int serial_putchar(char val, FILE *fp);
int serial_getchar(FILE *fp);
static FILE serial_stream = FDEV_SETUP_STREAM(serial_putchar, serial_getchar, _FDEV_SETUP_RW);

void main ()
{
	int i; 
	char buffer;
	FILE *fpi, *fpo;	

	USART_Init();
	
	fpi = stdin;
	fpo = stdout;

	while(1) {
		fscanf(fpi,"%c",&buffer);
		i = buffer;
		fprintf(fpo,"The ascii value of %c is: %d\n",buffer,i);
	}
}

void USART_Init( void )
{
	/* Baud rate: 9600
	 * UBRRn = 8Mhz/(16 * Baud) - 1
	 * UBRRn = 51
	 * Where UBRRnH is the four most significant bits
	 */
	UBRR0H = 0;
	UBRR0L = 51; 
	
	//make sure double transmission speed is disabled
	UCSR0A &= ~(1<<U2X0);

	/* enable transmission and recieving 
	 * TXENn is for Transimission
	 * RXENn is for Reciving
	 */ 
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	// set frame format: 8 data, 2 stop bits	
	UCSR0C = (1<<USBS0) | (3<<UCSZ00);

	stdin=&serial_stream;
	stdout=&serial_stream;
}

// Open the stream to write
int serial_putchar(char val, FILE *fp) {

	// Wait until empty, then write value
  	while((UCSR0A&(1<<UDRE0)) == 0);
   	UDR0 = val;
   	return 0;
}

// Wait until a character is available, then read it
int serial_getchar(FILE *fp) {
	// Wait for a character
   	while((UCSR0A&(1<<RXC0)) == 0);
   	return UDR0;
}     
