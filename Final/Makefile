all:
	avr-gcc -Wl,-u,vfprintf -lprintf_flt -lm -mmcu=atmega88 avrwave.c
	avr-objcopy -j .text -j .data -O ihex a.out a.hex
	gcc rpi.c -o serial

fuse:
	sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88p -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m

flash:
	sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88p -U flash:w:a.hex:i

clean: 
	rm -rf a.hex a.out serial
