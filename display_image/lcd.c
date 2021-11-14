#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "gpio.h"
#include "spi.h"

int LCD_Init(void) {
    if (GPIO_Init()) {
        printf("Error in GPIO_Init()\n");
        return 1;
    }

    if (SPI0_Init()) {
        printf("Error in SPI0_Init()\n");
        return 1;
    }

    return 0;
}


int LCD_WriteCommand(uint8_t command) {
    if (DC_Ctrl(GPIO_LOW)) {
        printf("Error in DC_Ctrl()\n");
        return 1;
    }
    if (SPI0_Write(&command, 1) != 1) {
        printf("Error in SPI0_Write()\n");
        return 1;
    }
    if (DC_Ctrl(GPIO_HIGH)) {
        printf("Error in DC_Ctrl()\n");
        return 1;
    }

    return 0;
}


int LCD_WriteData(uint8_t* data, uint8_t data_len) {
    if (SPI0_Write(data, data_len) != data_len) {
        printf("Error in SPI0_Write()\n");
        return 1;
    }

    return 0;
}


int LCD_DeInit(void) {
    if (SPI0_DeInit()) {
        printf("Error in SPI0_DeInit()\n");
        return 1;
    }
    if (GPIO_DeInit()) {
        printf("Error in GPIO_DeInit()\n");
        return 1;
    }

    return 0;
}
