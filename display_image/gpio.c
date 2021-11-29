//Reference code: https://elinux.org/RPi_GPIO_Code_Samples#sysfs
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "gpio.h"

static int cs_fd;
static int dc_fd;
static int rst_fd;

int GPIO_Init(void) {
    int exp_fd = 0, dir_fd = 0;
    int sys_status;

    //enable CS
    exp_fd = open(GPIO_EXPORT_PATH, O_WRONLY);
    if (exp_fd < 0) {
        perror("open");
        return 1;
    }

    sys_status = write(exp_fd, CS_GPIO_PIN_STR, 2);
    if (sys_status != 2) {
        perror("write");
        return 1;
    }

    close(exp_fd);
    //printf("Exported GPIO25\n");

    //enable DC
    exp_fd = open(GPIO_EXPORT_PATH, O_WRONLY);
    if (exp_fd < 0) {
        perror("open");
        return 1;
    }

    sys_status = write(exp_fd, DC_GPIO_PIN_STR, 2);
    if (sys_status != 2) {
        perror("write");
        return 1;
    }

    close(exp_fd);
    //printf("Exported GPIO24\n");

    //enable RST
    exp_fd = open(GPIO_EXPORT_PATH, O_WRONLY);
    if (exp_fd < 0) {
        perror("open");
        return 1;
    }

    sys_status = write(exp_fd, RST_GPIO_PIN_STR, 2);
    if (sys_status != 2) {
        perror("write");
        return 1;
    }

    close(exp_fd);
    //printf("Exported GPIO23\n");

    //set gpio25 to output
    dir_fd = open(CS_GPIO_PIN_DIR_PATH, O_WRONLY);
    if (dir_fd < 0) {
        perror("open");
        return 1;
    }

    sys_status = write(dir_fd, "out", 3);
    if (sys_status != 3) {
        perror("write");
        return 1;
    }

    close(dir_fd);
    //printf("Set GPIO25 as output\n");

    //set gpio24 to output
    dir_fd = open(DC_GPIO_PIN_DIR_PATH, O_WRONLY);
    if (dir_fd < 0) {
        perror("open");
        return 1;
    }

    sys_status = write(dir_fd, "out", 3);
    if (sys_status != 3) {
        perror("write");
        return 1;
    }

    close(dir_fd);
    //printf("Set GPIO24 as output\n");

    //set gpio23 to output
    dir_fd = open(RST_GPIO_PIN_DIR_PATH, O_WRONLY);
    if (dir_fd < 0) {
        perror("open");
        return 1;
    }

    sys_status = write(dir_fd, "out", 3);
    if (sys_status != 3) {
        perror("write");
        return 1;
    }

    close(dir_fd);
    //printf("Set GPIO23 as output\n");

    //open gpio ports
    cs_fd = open(CS_GPIO_PIN_VAL_PATH, O_WRONLY);
    if (cs_fd < 0) {
        perror("open");
        return 1;
    }

    dc_fd = open(DC_GPIO_PIN_VAL_PATH, O_WRONLY);
    if (cs_fd < 0) {
        perror("open");
        return 1;
    }

    rst_fd = open(RST_GPIO_PIN_VAL_PATH, O_WRONLY);
    if (cs_fd < 0) {
        perror("open");
        return 1;
    }

    sys_status = write(cs_fd, "1", 1);
    if (sys_status != 1) {
        printf("Did not write output 0\n");
    }

    sys_status = write(dc_fd, "1", 1);
    if (sys_status != 1) {
        printf("Did not write output 0\n");
    }

    sys_status = write(rst_fd, "1", 1);
    if (sys_status != 1) {
        printf("Did not write output 0\n");
    }

    //printf("Opened CS\n");
    //printf("Opened DC\n");
    //printf("Opened RST\n");

    return 0;
}


int CS_Ctrl(int level) {
    int sys_status;
    if (level == 0) {
        sys_status = write(cs_fd, "0", 1);
        if (sys_status != 1) {
            printf("Did not write output 0\n");
            return 1;
        }
    }
    else if (level == 1) {
        sys_status = write(cs_fd, "1", 1);
        if (sys_status != 1) {
            printf("Did not write output 1\n");
            return 1;
        }
    }

    return 0;
}


int DC_Ctrl(int level) {
    int sys_status;
    if (level == 0) {
        sys_status = write(dc_fd, "0", 1);
        if (sys_status != 1) {
            printf("Did not write output 0\n");
            return 1;
        }
    }
    else if (level == 1) {
        sys_status = write(dc_fd, "1", 1);
        if (sys_status != 1) {
            printf("Did not write output 1\n");
            return 1;
        }
    }

    return 0;
}


int RST_Ctrl(int level) {
    int sys_status;
    if (level == 0) {
        sys_status = write(rst_fd, "0", 1);
        if (sys_status != 1) {
            printf("Did not write output 0\n");
            return 1;
        }
    }
    else if (level == 1) {
        sys_status = write(rst_fd, "1", 1);
        if (sys_status != 1) {
            printf("Did not write output 1\n");
            return 1;
        }
    }

    return 0;
}


int GPIO_DeInit(void) {
    int unexp_fd;
    int sys_status;

    //close gpio file descriptors
    sys_status = close(cs_fd);
    if (sys_status == -1) {
        perror("close");
        return 1;
    }

    sys_status = close(dc_fd);
    if (sys_status == -1) {
        perror("close");
        return 1;
    }

    sys_status = close(rst_fd);
    if (sys_status == -1) {
        perror("close");
        return 1;
    }

    //deinit gpio25
    unexp_fd = open(GPIO_UNEXPORT_PATH, O_WRONLY);
    if (unexp_fd < 0) {
        perror("open");
        return 1;
    }

    sys_status = write(unexp_fd, CS_GPIO_PIN_STR, 2);
    if (sys_status != 2) {
        perror("write");
        return 1;
    }

    close(unexp_fd);
    //printf("Unexported GPIO25\n");

    //deinit gpio24
    unexp_fd = open(GPIO_UNEXPORT_PATH, O_WRONLY);
    if (unexp_fd < 0) {
        perror("open");
        return 1;
    }

    sys_status = write(unexp_fd, DC_GPIO_PIN_STR, 2);
    if (sys_status != 2) {
        perror("write");
        return 1;
    }

    close(unexp_fd);
    //printf("Unexported GPIO24\n");

    //deinit gpio23
    unexp_fd = open(GPIO_UNEXPORT_PATH, O_WRONLY);
    if (unexp_fd < 0) {
        perror("open");
        return 1;
    }

    sys_status = write(unexp_fd, RST_GPIO_PIN_STR, 2);
    if (sys_status != 2) {
        perror("write");
        return 1;
    }

    close(unexp_fd);
    //printf("Unexported GPIO23\n");

    return 0;
}
