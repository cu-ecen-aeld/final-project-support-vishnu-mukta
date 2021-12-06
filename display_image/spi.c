#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include "spi.h"

static int spi_fd;


int SPI0_Init(void) {
    int mode = SPI_MODE_0;
    int speed = SPI_CLK_SPEED;
    int bits = 8;
    int sys_status;

    spi_fd = open("/dev/spidev0.0", O_RDWR);
    if (spi_fd < 0) {
        perror("open");
        return 1;
    }

    syslog(LOG_INFO, "Opened spidev0.0\n");

    sys_status = ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    if (sys_status < 0) {
        perror("ioctl (SPI_IOC_WR_MODE)");
        return 1;
    }

    syslog(LOG_INFO, "WR mode set\n");

    sys_status = ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (sys_status < 0) {
        perror("ioctl (SPI_IOC_WR_BITS_PER_WORD)");
        return 1;
    }

    syslog(LOG_INFO, "WR bits per word set\n");

    sys_status = ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (sys_status < 0) {
        perror("ioctl (SPI_IOC_WR_MAX_SPEED_HZ)");
        return 1;
    }

    syslog(LOG_INFO, "WR speed set\n");

    return 0;
}


int SPI0_Write(uint8_t* w_buff, uint8_t w_buff_len) {
    int bytes_written;

    bytes_written = write(spi_fd, w_buff, w_buff_len);
    if (bytes_written == -1) {
        perror("write");
        return -1;
    }
    else if (bytes_written != w_buff_len) {
        syslog(LOG_ERR, "Did not write full buffer\n");
    }

    return bytes_written;
}


int SPI0_DeInit(void) {
    int sys_status;
    
    sys_status = close(spi_fd);
    if (sys_status == -1) {
        perror("close");
        return 1;
    }

    syslog(LOG_INFO, "Closed spidev0.0\n");

    return 0;
}
