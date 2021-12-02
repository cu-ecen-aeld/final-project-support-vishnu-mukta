//Reference code: https://github.com/adafruit/Adafruit_ILI9341

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "lcd.h"
#include "gpio.h"
#include "spi.h"


#define MADCTL_MY 0x80  ///< Bottom to top
#define MADCTL_MX 0x40  ///< Right to left
#define MADCTL_MV 0x20  ///< Reverse Mode
#define MADCTL_ML 0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00 ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08 ///< Blue-Green-Red pixel order
#define MADCTL_MH 0x04  ///< LCD refresh right to left

#define BLUE_MASK (0x1F)
#define GREEN_MASK (0x3F)
#define RED_MASK (0x1F)

#define BLUE_SHIFT (0)
#define GREEN_SHIFT (5)
#define RED_SHIFT (11)


int LCD_Init(void) {
    if (GPIO_Init()) {
        printf("Error in GPIO_Init()\n");
        return 1;
    }

    if (SPI0_Init()) {
        printf("Error in SPI0_Init()\n");
        return 1;
    }

    //init sequence, from begin() function in https://github.com/adafruit/Adafruit_ILI9341/blob/master/Adafruit_ILI9341.cpp
    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    if (RST_Ctrl(GPIO_LOW)) {
        printf("Error in RST_Ctrl()\n");
        return 1;
    }

    usleep(50000);
    
    if (RST_Ctrl(GPIO_HIGH)) {
        printf("Error in RST_Ctrl()\n");
        return 1;
    }

    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150000);


    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_SWRESET)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150000);

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xEF)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x03)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x80)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x02)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xCF)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0xC1)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x30)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xED)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x64)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x03)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x12)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x81)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xE8)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x85)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x78)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xCB)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x39)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x2C)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x34)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x02)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xF7)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x20)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xEA)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_PWCTR1)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x23)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_PWCTR2)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x10)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_VMCTR1)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x3e)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x28)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_VMCTR2)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x86)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
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
    if(LCD_SendDataByte(0x48)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_VSCRSADD)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_PIXFMT)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x55)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_FRMCTR1)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x18)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_DFUNCTR)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x08)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x82)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x27)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xF2)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_GAMMASET)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x01)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_GMCTRP1)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0F)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x31)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x2B)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0C)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0E)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x08)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x4E)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0xF1)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x37)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x07)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x10)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x03)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0E)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x09)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_GMCTRN1)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0E)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x14)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x03)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x11)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x07)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x31)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0xC1)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x48)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x08)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0F)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0C)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x31)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x36)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0F)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_SLPOUT)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x80)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150000);

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_DISPON)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x80)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150000);

    return 0;
}


int LCD_SendCommandByte(uint8_t command) {
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


int LCD_SendDataByte(uint8_t data) {
    if (SPI0_Write(&data, 1) != 1) {
        printf("Error in SPI0_Write()\n");
        return 1;
    }

    return 0;
}


int LCD_SetOrientation(void) {
    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_MADCTL)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    return 0;
}


int LCD_SetBorders(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_CASET)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(x1 >> 8))) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)y1)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(y1 >> 8))) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)x2)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_PASET)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(x2 >> 8))) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)x2)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(y2 >> 8))) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)y2)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_RAMWR)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    return 0;
}


int LCD_SetAddress(uint16_t x, uint16_t y) {
    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_CASET)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(x >> 8))) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)x)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(x >> 8))) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)x)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_PASET)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(y >> 8))) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)y)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(y >> 8))) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)y)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    return 0;
}


int LCD_WritePixel(uint16_t color) {
    if (CS_Ctrl(GPIO_LOW)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_RAMWR)) {
        printf("Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(color >> 8))) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)color)) {
        printf("Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        printf("Error in CS_Ctrl()\n");
        return 1;
    }

    return 0;
}


int LCD_WritePGMPixel(uint16_t x, uint16_t y, uint8_t color) {
    uint16_t pix_color = 0;
    pix_color |= ((color >> 3) & BLUE_MASK) << BLUE_SHIFT;
    pix_color |= ((color >> 2) & GREEN_MASK) << GREEN_SHIFT;
    pix_color |= ((color >> 3) & RED_MASK) << RED_SHIFT;

//    printf("X address: %d, Y address: %d\n", x, y);
//    printf("0x%04X\n", pix_color);
//    printf("%d\n", ((pix_color << BLUE_SHIFT) & BLUE_MASK) >> BLUE_SHIFT);
//    printf("%d\n", ((pix_color << BLUE_SHIFT) & BLUE_MASK) >> BLUE_SHIFT);
//    printf("%d\n\n", ((pix_color << BLUE_SHIFT) & BLUE_MASK) >> BLUE_SHIFT);

    LCD_SetAddress(x, y);
    LCD_WritePixel(pix_color);
    return 1;
}


int LCD_WritePPMPixel(uint16_t x, uint16_t y, uint8_t* color) {
    uint16_t pix_color = 0;
    pix_color |= ((color[2] >> 3) & BLUE_MASK) << BLUE_SHIFT;
    pix_color |= ((color[1] >> 2) & GREEN_MASK) << GREEN_SHIFT;
    pix_color |= ((color[0] >> 3) & RED_MASK) << RED_SHIFT;

//    printf("X address: %d, Y address: %d\n", x, y);
//    printf("0x%04X\n", pix_color);
//    printf("%d\n", ((pix_color << BLUE_SHIFT) & BLUE_MASK) >> BLUE_SHIFT);
//    printf("%d\n", ((pix_color << BLUE_SHIFT) & BLUE_MASK) >> BLUE_SHIFT);
//    printf("%d\n\n", ((pix_color << BLUE_SHIFT) & BLUE_MASK) >> BLUE_SHIFT);

    LCD_SetAddress(x, y);
    LCD_WritePixel(pix_color);
    return 1;
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
