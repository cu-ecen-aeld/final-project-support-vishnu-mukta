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

int main(void) {
    int lcd_spi_fd = 0;
    int mode = SPI_MODE_0;
    int speed = 1000000;
    int bits = 8;
    int sys_status = 0;
    uint8_t test_array[2] = { 0x83, 0x87 };
    printf("Entering program...\n");

    lcd_spi_fd = open("/dev/spidev0.0", O_RDWR);
    if (lcd_spi_fd < 0) {
        perror("open");
        return 1;
    }

    printf("Opened spidev0.0\n");

    sys_status = ioctl(lcd_spi_fd, SPI_IOC_WR_MODE, &mode);
    if (sys_status < 0) {
        perror("SPI_IOC_WR_MODE");
        return 1;
    }

    printf("Set WR mode\n");

    sys_status = ioctl(lcd_spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (sys_status < 0) {
        perror("SPI_IOC_WR_BITS_PER_WORD");
        return 1;
    }

    printf("Set WR bits per word\n");

    sys_status = ioctl(lcd_spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (sys_status < 0) {
        perror("SPI_IOC_WR_MAX_SPEED_HZ");
        return 1;
    }

    printf("Set WR speed\n");


    sys_status = write(lcd_spi_fd, test_array, 2);
    if (sys_status == -1) {
        perror("write");
        return 1;
    }
    else if (sys_status != 2) {
        printf("Did not write full test_array\n");
    }

    printf("Check Logic Analyzer Output\n");


    sys_status = close(lcd_spi_fd);
    if (sys_status == -1) {
        perror("close");
        return 1;
    }

    printf("Closed spidev0.0\n");

    return 0;
}
