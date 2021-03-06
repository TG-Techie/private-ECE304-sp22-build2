# makefile for AVR projects
# revision history
#	Date		Author			Revision
#	2/14/22		D. McLaughlin	initial release 
# 	2/15/22		D. McLaughlin	updated with corrections (thanks S. Kaza)
#	3/30/22		D. McLaughlin	updated for use with Sparkfun Pocket Programmer

# Specify the name of your source code here:
SOURCEFILE = src/*.c libs/*.c
# Use 1000000 for a new ATmega328P IC; use 16000000 for Arduino Uno
CLOCKSPEED = 16000000	
# Use usbtiny for the Sparkfun Pocket Programmer; Arduino for Arduino Uno
PROGRAMMER = usbtiny

build:	clean	main.hex

main.hex:	clean	main.elf 
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=atmega328p main.elf

main.elf:
	avr-gcc -O3 -Ilibs/ -Werror -Wno-main  -DF_CPU=$(CLOCKSPEED) -mmcu=atmega328p -o main.elf $(SOURCEFILE)


flash:	build
	avrdude -c $(PROGRAMMER) -p atmega328p -U flash:w:main.hex:i -C avrdude.conf

erase:
	avrdude -c $(PROGRAMMER) -p atmega328p  -e -C avrdude.conf

clean:
	- rm -f main.hex main.elf
