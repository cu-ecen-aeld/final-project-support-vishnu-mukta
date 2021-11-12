/*
 * File name: display_image.c - Receives image from socket and displays on LCD
 * Author: Vishnu Dodballapur
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int lcd_spi_fd = 0;
    int sys_status = 0;

    printf("Entering program...\n");

    lcd_spi_fd = open("/dev/spidev0.0", O_RDWR);
    if (lcd_spi_fd == -1) {
        perror("open");
        return 1;
    }

    printf("Opened spi0.0\n");

    sys_status = close(lcd_spi_fd);
    if (sys_status == -1) {
        perror("close");
        return 1;
    }

    printf("Closed spi0.0\n");

    return 0;
}
