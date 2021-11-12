ifeq ($(CC),)
	CC = $(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	CFLAGS = -g -Wall -Werror 
endif

ifeq ($(LDFLAGS),)
	LDFLAGS = -pthread -lrt
endif

all: capture.o capture

default: capture.o capture

capture.o : capture.c
	$(CC) $(CFLAGS) -c -o capture.o capture.c $(INCLUDES)

capture : capture.o
	$(CC) $(CFLAGS) capture.o -o capture $(INCLUDES) $(LDFLAGS)

clean:
	-rm -f *.o *.elf *.map
