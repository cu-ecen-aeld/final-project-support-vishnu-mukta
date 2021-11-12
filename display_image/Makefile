CC=$(CROSS_COMPILE)gcc
CFLAGS = -g -Wall -Werror

all: display_image

default: display_image

display_image: display_image.c
	$(CC) -c -o display_image.o display_image.c $(CFLAGS)
	$(CC) -o display_image display_image.o

clean:
	rm -f display_image *.o
