#ifndef __LCD_H
#define __LCD_H

#include <stdint.h>

#define LCD_DUMMY_CMD (0x12)

int LCD_Init(void);
int LCD_WriteCommand(uint8_t command);
int LCD_WriteData(uint8_t* data, uint8_t data_len);
int LCD_DeInit(void);

#endif // __LCD_H
