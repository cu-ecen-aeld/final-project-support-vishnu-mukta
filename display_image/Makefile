CC=$(CROSS_COMPILE)gcc
CFLAGS = -g -Wall -Werror

all: display_image

default: display_image

display_image: display_image.o lcd.o spi.o gpio.o
	$(CC) -o display_image display_image.o lcd.o spi.o gpio.o

display_image.o: display_image.c lcd.h spi.h gpio.h
	$(CC) $(CFLAGS) -c -o display_image.o display_image.c

lcd.o: lcd.c lcd.h spi.h gpio.h
	$(CC) $(CFLAGS) -c -o lcd.o lcd.c

spi.o: spi.c spi.h
	$(CC) $(CFLAGS) -c -o spi.o spi.c

gpio.o: gpio.c gpio.h
	$(CC) $(CFLAGS) -c -o gpio.o gpio.c

clean:
	rm -f display_image *.o
