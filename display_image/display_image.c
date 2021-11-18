/*
 * File name: display_image.c - Receives image from socket and displays on LCD
 * Author: Vishnu Dodballapur
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <syslog.h>
#include <string.h>
#include "gpio.h"
#include "lcd.h"


int main(int argc, char* argv[]) {
    //int socket_fd;
    struct addrinfo hints;
    struct addrinfo* res;

    if (argc != 2) {
        printf("Incorrect number of arguments. Format should be: $ ./display_image [ server ip address ] \n");
        exit(-1);
    }

    openlog(NULL, 0, LOG_USER);
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(argv[1], "9000", &hints, &res) != 0 ) {
        syslog(LOG_ERR, "getaddrinfo");
        exit(-1);
    }

    /*
    uint16_t color = 0xFFE0;
    int i, j;
    printf("Entering program...\n");

    //Init LCD module
    if (LCD_Init()) {
        printf("Error in LCD_Init()\n");
        return 1;
    }

    //Init LCD module
    if (LCD_SetOrientation()) {
        printf("Error in LCD_SendOrientation()\n");
        return 1;
    }

    //Init LCD module
    if (LCD_SetBorders(0, 0, 239, 319)) {
        printf("Error in LCD_SetBorders()\n");
        return 1;
    }

    printf("Init LCD complete...\n");

    printf("Drawing pixel...\n");
    for (j = 0; j < 40; j++) {
        for (i = 0; i < 240; i++) {
            LCD_SetAddress(i, j);
            LCD_WritePixel(color);
        }
    }

    //DeInit LCD module
    if (LCD_DeInit()) {
        printf("Error in LCD_DeInit()\n");
        return 1;
    }
    */

    return 0;
}
