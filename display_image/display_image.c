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
    /*
    int socket_fd;
    struct addrinfo hints;
    struct addrinfo* res;
    uint8_t recv_buff[15] = { 0 };

    if (argc != 2) {
        printf("Incorrect number of arguments.\nUsage:\n./display_image [ server ip address ] \n");
        exit(-1);
    }

    openlog(NULL, 0, LOG_USER);
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(argv[1], "9000", &hints, &res) != 0 ) {
        syslog(LOG_ERR, "getaddrinfo");
        perror("getaddrinfo");
        exit(-1);
    }


    socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (socket_fd < 0) {
        syslog(LOG_ERR, "socket");
        perror("socket");
        exit(-1);
    }

    if (connect(socket_fd, res->ai_addr, res->ai_addrlen) == -1) {
        syslog(LOG_ERR, "connect");
        perror("connect");
        exit(-1);
    }

    printf("Connected!\n");

    int send_bytes;
    send_bytes = send(socket_fd, "Hello, Mukta!\n", 14, 0);
    if (send_bytes < 0) {
        syslog(LOG_ERR, "send");
        perror("send");
        exit(-1);
    }

    printf("Bytes sent: %d\n", send_bytes);

    int recv_bytes;
    recv_bytes = recv(socket_fd, recv_buff, 14, 0);
    if (recv_bytes < 0) {
        syslog(LOG_ERR, "recv");
        perror("recv");
        exit(-1);
    }

    printf("Bytes recvd: %d\n", recv_bytes);
    printf("Message received from socket server: %s\n", (char *)recv_buff);
    */

    
    uint16_t color = 0x001F; //Blue
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
    if (LCD_SetBorders(0, 0, 319, 239)) {
        printf("Error in LCD_SetBorders()\n");
        return 1;
    }

    printf("Init LCD complete...\n");

    printf("Drawing pixel...\n");
    for (j = 0; j < 40; j++) {
        for (i = 0; i < 320; i++) {
            LCD_SetAddress(i, j);
            LCD_WritePixel(color);
        }
    }

    //DeInit LCD module
    if (LCD_DeInit()) {
        printf("Error in LCD_DeInit()\n");
        return 1;
    }
    

    return 0;
}
