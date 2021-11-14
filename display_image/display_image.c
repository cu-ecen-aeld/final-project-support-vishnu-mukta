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

int main(void) {
    uint8_t test_array[2] = { 0x83, 0x87 };
    printf("Entering program...\n");

    //Init LCD module
    if (LCD_Init()) {
        printf("Error in LCD_Init()\n");
        return 1;
    }

    //Test LCD module
    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    if(LCD_WriteCommand(LCD_DUMMY_CMD)) {
        printf("We gotta problem in LCD_WriteCommand()\n");
    }

    if(LCD_WriteData(test_array, 2)) {
        printf("We gotta problem in LCD_WriteData()\n");
    }

    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    printf("Check Logic Analyzer Output\n");

    //DeInit LCD module
    if (LCD_DeInit()) {
        printf("Error in LCD_DeInit()\n");
        return 1;
    }

    return 0;
}
