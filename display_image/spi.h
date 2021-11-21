#ifndef __SPI_H
#define __SPI_H

#include <stdint.h>

#define SPI_CLK_SPEED  (12000000)

int SPI0_Init(void);
int SPI0_Write(uint8_t* w_buff, uint8_t w_buff_len);
int SPI0_DeInit(void);

#endif // __SPI_H
