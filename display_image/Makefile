CROSS_COMPILE=
CC=gcc
CFLAGS = -g -Wall -Werror

all: display_image

default: display_image

display_image: display_image.c
	${CROSS_COMPILE}${CC} -c -o display_image.o display_image.c ${CFLAGS}
	${CROSS_COMPILE}${CC} -o display_image display_image.o

clean:
	rm -f display_image *.o