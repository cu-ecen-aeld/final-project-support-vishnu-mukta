//Reference code: https://github.com/adafruit/Adafruit_ILI9341

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <syslog.h>
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
        syslog(LOG_ERR, "Error in GPIO_Init()\n");
        return 1;
    }

    if (SPI0_Init()) {
        syslog(LOG_ERR, "Error in SPI0_Init()\n");
        return 1;
    }

    //init sequence, from begin() function in https://github.com/adafruit/Adafruit_ILI9341/blob/master/Adafruit_ILI9341.cpp
    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    if (RST_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in RST_Ctrl()\n");
        return 1;
    }

    usleep(50000);
    
    if (RST_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in RST_Ctrl()\n");
        return 1;
    }

    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150000);


    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_SWRESET)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150000);

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xEF)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x03)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x80)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x02)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xCF)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0xC1)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x30)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xED)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x64)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x03)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x12)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x81)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xE8)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x85)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x78)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xCB)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x39)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x2C)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x34)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x02)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xF7)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x20)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xEA)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_PWCTR1)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x23)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_PWCTR2)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x10)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_VMCTR1)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x3e)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x28)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }


    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_VMCTR2)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x86)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_MADCTL)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x48)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_VSCRSADD)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_PIXFMT)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x55)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_FRMCTR1)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x18)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_DFUNCTR)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x08)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x82)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x27)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(0xF2)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_GAMMASET)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x01)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_GMCTRP1)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0F)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x31)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x2B)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0C)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0E)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x08)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x4E)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0xF1)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x37)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x07)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x10)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x03)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0E)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x09)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_GMCTRN1)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x00)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0E)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x14)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x03)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x11)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x07)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x31)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0xC1)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x48)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x08)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0F)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0C)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x31)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x36)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x0F)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150);

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_SLPOUT)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x80)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150000);

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_DISPON)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(0x80)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    usleep(150000);

    return 0;
}


int LCD_SendCommandByte(uint8_t command) {
    if (DC_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in DC_Ctrl()\n");
        return 1;
    }
    if (SPI0_Write(&command, 1) != 1) {
        syslog(LOG_ERR, "Error in SPI0_Write()\n");
        return 1;
    }
    if (DC_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in DC_Ctrl()\n");
        return 1;
    }

    return 0;
}


int LCD_SendDataByte(uint8_t data) {
    if (SPI0_Write(&data, 1) != 1) {
        syslog(LOG_ERR, "Error in SPI0_Write()\n");
        return 1;
    }

    return 0;
}


int LCD_SetOrientation(void) {
    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_MADCTL)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    return 0;
}


int LCD_SetBorders(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_CASET)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(x1 >> 8))) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)y1)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(y1 >> 8))) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)x2)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_PASET)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(x2 >> 8))) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)x2)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(y2 >> 8))) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)y2)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_RAMWR)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    return 0;
}


int LCD_SetAddress(uint16_t x, uint16_t y) {
    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_CASET)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(x >> 8))) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)x)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(x >> 8))) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)x)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_PASET)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(y >> 8))) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)y)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(y >> 8))) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)y)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    return 0;
}


int LCD_WritePixel(uint16_t color) {
    if (CS_Ctrl(GPIO_LOW)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }
    if(LCD_SendCommandByte(ILI9341_RAMWR)) {
        syslog(LOG_ERR, "Error in LCD_SendCommandByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)(color >> 8))) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if(LCD_SendDataByte((uint8_t)color)) {
        syslog(LOG_ERR, "Error in LCD_SendDataByte()\n");
        return 1;
    }
    if (CS_Ctrl(GPIO_HIGH)) {
        syslog(LOG_ERR, "Error in CS_Ctrl()\n");
        return 1;
    }

    return 0;
}


int LCD_WritePGMPixel(uint16_t x, uint16_t y, uint8_t color) {
    uint16_t pix_color = 0;
    pix_color |= ((color >> 3) & BLUE_MASK) << BLUE_SHIFT;
    pix_color |= ((color >> 2) & GREEN_MASK) << GREEN_SHIFT;
    pix_color |= ((color >> 3) & RED_MASK) << RED_SHIFT;

    LCD_SetAddress(x, y);
    LCD_WritePixel(pix_color);
    return 1;
}


int LCD_WritePPMPixel(uint16_t x, uint16_t y, uint8_t* color) {
    uint16_t pix_color = 0;
    pix_color |= ((color[2] >> 3) & BLUE_MASK) << BLUE_SHIFT;
    pix_color |= ((color[1] >> 2) & GREEN_MASK) << GREEN_SHIFT;
    pix_color |= ((color[0] >> 3) & RED_MASK) << RED_SHIFT;

    LCD_SetAddress(x, y);
    LCD_WritePixel(pix_color);
    return 1;
}


int LCD_DeInit(void) {
    if (SPI0_DeInit()) {
        syslog(LOG_ERR, "Error in SPI0_DeInit()\n");
        return 1;
    }
    if (GPIO_DeInit()) {
        syslog(LOG_ERR, "Error in GPIO_DeInit()\n");
        return 1;
    }

    return 0;
}
