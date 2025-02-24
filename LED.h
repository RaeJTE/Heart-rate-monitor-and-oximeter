#ifndef LED_H
#define LED_H
#include <stm32f429xx.h>


// function prototypes
void LED_INIT(void);
void toggle_PCB_IF(void);
void toggle_PCB_RED(void);
void Toggle_BLUE(void);
void ON_GRN(void);
void Toggle_LED(uint8_t led);

#endif