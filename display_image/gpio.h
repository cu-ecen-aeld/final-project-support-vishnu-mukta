#ifndef __GPIO_H
#define __GPIO_H

#define GPIO_EXPORT_PATH "/sys/class/gpio/export"
#define GPIO_UNEXPORT_PATH "/sys/class/gpio/unexport"

#define CS_GPIO_PIN (25) //1-22
#define CS_GPIO_PIN_STR "25"
#define CS_GPIO_PIN_DIR_PATH "/sys/class/gpio/gpio25/direction"
#define CS_GPIO_PIN_VAL_PATH "/sys/class/gpio/gpio25/value"

#define DC_GPIO_PIN (24) //1-18
#define DC_GPIO_PIN_STR "24"
#define DC_GPIO_PIN_DIR_PATH "/sys/class/gpio/gpio24/direction"
#define DC_GPIO_PIN_VAL_PATH "/sys/class/gpio/gpio24/value"

#define GPIO_LOW    (0)
#define GPIO_HIGH   (1)

int GPIO_Init(void);
int CS_Ctrl(int level);
int DC_Ctrl(int level);
int GPIO_DeInit(void);


#endif // __GPIO_H
