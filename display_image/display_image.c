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
#include "gpio.h"
#include "lcd.h"


#define MADCTL_MY 0x80  ///< Bottom to top
#define MADCTL_MX 0x40  ///< Right to left
#define MADCTL_MV 0x20  ///< Reverse Mode
#define MADCTL_ML 0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00 ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08 ///< Blue-Green-Red pixel order
#define MADCTL_MH 0x04  ///< LCD refresh right to left

int main(void) {
    uint16_t x = 12, y = 19, color = 0xFFE0;
    int i, j;
    printf("Entering program...\n");

    //Init LCD module
    if (LCD_Init()) {
        printf("Error in LCD_Init()\n");
        return 1;
    }

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_MADCTL)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(MADCTL_MX | MADCTL_BGR)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    printf("Init LCD complete...\n");

    printf("Drawing pixel...\n");
    for (j = 0; j < 40; j++) {
        for (i = 0; i < 240; i++) {
            LCD_SetAddress(x, y);
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
