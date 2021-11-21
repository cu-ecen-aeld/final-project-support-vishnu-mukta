//Reference code: https://github.com/adafruit/Adafruit_ILI9341

#ifndef __LCD_H
#define __LCD_H

#include <stdint.h>

#define LCD_WIDTH (320)
#define LCD_HEIGHT (240)

#define PGM_HEADER_LEN  (49)

#define ILI9341_NOP (0x00)     ///< No-op register
#define ILI9341_SWRESET (0x01) ///< Software reset register
#define ILI9341_RDDID (0x04)   ///< Read display identification information
#define ILI9341_RDDST (0x09)   ///< Read Display Status

#define ILI9341_SLPIN (0x10)  ///< Enter Sleep Mode
#define ILI9341_SLPOUT (0x11) ///< Sleep Out
#define ILI9341_PTLON (0x12)  ///< Partial Mode ON
#define ILI9341_NORON (0x13)  ///< Normal Display Mode ON

#define ILI9341_RDMODE (0x0A)     ///< Read Display Power Mode
#define ILI9341_RDMADCTL (0x0B)   ///< Read Display MADCTL
#define ILI9341_RDPIXFMT (0x0C)   ///< Read Display Pixel Format
#define ILI9341_RDIMGFMT (0x0D)   ///< Read Display Image Format
#define ILI9341_RDSELFDIAG (0x0F) ///< Read Display Self-Diagnostic Result

#define ILI9341_INVOFF (0x20)   ///< Display Inversion OFF
#define ILI9341_INVON (0x21)    ///< Display Inversion ON
#define ILI9341_GAMMASET (0x26) ///< Gamma Set
#define ILI9341_DISPOFF (0x28)  ///< Display OFF
#define ILI9341_DISPON (0x29)   ///< Display ON

#define ILI9341_CASET (0x2A) ///< Column Address Set
#define ILI9341_PASET (0x2B) ///< Page Address Set
#define ILI9341_RAMWR (0x2C) ///< Memory Write
#define ILI9341_RAMRD (0x2E) ///< Memory Read

#define ILI9341_PTLAR (0x30)    ///< Partial Area
#define ILI9341_VSCRDEF (0x33)  ///< Vertical Scrolling Definition
#define ILI9341_MADCTL (0x36)   ///< Memory Access Control
#define ILI9341_VSCRSADD (0x37) ///< Vertical Scrolling Start Address
#define ILI9341_PIXFMT (0x3A)   ///< COLMOD: Pixel Format Set

#define ILI9341_FRMCTR1                                                        \
  (0xB1) ///< Frame Rate Control (In Normal Mode/Full Colors)
#define ILI9341_FRMCTR2 (0xB2) ///< Frame Rate Control (In Idle Mode/8 colors)
#define ILI9341_FRMCTR3                                                        \
  (0xB3) ///< Frame Rate control (In Partial Mode/Full Colors)
#define ILI9341_INVCTR (0xB4)  ///< Display Inversion Control
#define ILI9341_DFUNCTR (0xB6) ///< Display Function Control

#define ILI9341_PWCTR1 (0xC0) ///< Power Control 1
#define ILI9341_PWCTR2 (0xC1) ///< Power Control 2
#define ILI9341_PWCTR3 (0xC2) ///< Power Control 3
#define ILI9341_PWCTR4 (0xC3) ///< Power Control 4
#define ILI9341_PWCTR5 (0xC4) ///< Power Control 5
#define ILI9341_VMCTR1 (0xC5) ///< VCOM Control 1
#define ILI9341_VMCTR2 (0xC7) ///< VCOM Control 2

#define ILI9341_RDID1 (0xDA) ///< Read ID 1
#define ILI9341_RDID2 (0xDB) ///< Read ID 2
#define ILI9341_RDID3 (0xDC) ///< Read ID 3
#define ILI9341_RDID4 (0xDD) ///< Read ID 4

#define ILI9341_GMCTRP1 (0xE0) ///< Positive Gamma Correction
#define ILI9341_GMCTRN1 (0xE1) ///< Negative Gamma Correction

int LCD_Init(void);
int LCD_SendCommandByte(uint8_t command);
int LCD_SendDataByte(uint8_t data);
int LCD_SetOrientation(void);
int LCD_SetBorders(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
int LCD_SetAddress(uint16_t x, uint16_t y);
int LCD_WritePixel(uint16_t color);
int LCD_WritePGMPixel(uint16_t x, uint16_t y, uint8_t color);
int LCD_DeInit(void);

#endif // __LCD_H
