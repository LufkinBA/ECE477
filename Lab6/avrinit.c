/* Lab 6 
 * King Lufkin the Trusty
 * avrinit.c
 * The AVR program that sets up a UART connection with a Raspberry Pi
 * and reads the ADC value based off of the reference voltage that is 
 * set to the input voltage. 
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
void ADC_init(void);
int ADC_read(void);

int serial_putchar(char val, FILE *fp);
int serial_getchar(FILE *fp);
static FILE serial_stream = FDEV_SETUP_STREAM(serial_putchar, serial_getchar, _FDEV_SETUP_RW);

void update_clock_speed(void);

void main ()
{
	int ADC_val, a, x; 
	double Vcc; 
	char buffer[100];
	FILE *fpi, *fpo;	
	update_clock_speed();

	USART_Init();
	
	fpi = stdin;
	fpo = stdout;

	//Wait until AVR recieves the string START to begin 
/*	a = 1;
	x = 0;
	while (a)
	{
		fscanf(fpi,"%c",&buffer[x]);	
		scanf("%[START]",buffer);
		x++;
		if (!strcmp(buffer,"START"))
			a=0;
		fprintf(fpo,"%s\n",buffer);
	}
*/

	ADC_init();
	
	while (1) {
	
		ADC_val = ADC_read();
		
		Vcc = (1.1*1024.0)/(float)ADC_val;
			
		//Transmit ADC data
		fprintf(stdout,"The input voltage (Vcc) is: %lf \n", Vcc);
		
		_delay_ms(1000);
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


void update_clock_speed(void)
{
  char temp;
  temp=eeprom_read_byte((void *)1); //read oscillator offset sign 
                                    //0 is positive 1 is  negative
                                    //erased reads as ff (so avoid that)
  if(temp==0||temp==1)      //if sign is invalid, don't change oscillator
  {
      if(temp==0)
	  {
	     temp=eeprom_read_byte((void *)0);
		 if(temp != 0xff) OSCCAL+=temp;
	  }
	  else
	  {
	     temp=eeprom_read_byte((void *)0);
		 if(temp!=0xff) OSCCAL -=temp;
	  }
  }
}

//Function for initializing ADC
/* ADCSRA:
 * Enable ADC
 * Enable clock prescale value of 64: 8MHz/64 = 125kHz ->50kHz-200kHz ADC operates on
 *  
 * ADMUX:
 * Voltage Reference Selection as AVcc
 * Input channel selection for Bandgap voltage
 */
void ADC_init(void) 
{
	ADCSRA |= (1<<ADEN) | (6<<ADPS0);
	ADMUX |= (1<<REFS0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3); 
	
	_delay_ms(1000);
}

int ADC_read(void)
{
	char buff[10];
	int intbuf;
	
	//Start conversion by setting ADSC to 1
    ADCSRA |= (1<<ADSC);
    ADCSRB = 0;

    //wait for conversion to complete ~13 ADC clock cycles
    while(ADCSRA & (1<<ADSC));

    //ADCL holds the result of the conversion 
    //ADCL holds 8 LSB bits and ADCH holds 2 MSB
	intbuf = ADCL + (ADCH<<8);
	
	return intbuf;
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
