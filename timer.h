#ifndef timer
#define timer
#include <stm32f429xx.h>
#include "usart.h"
#include "LED.h"
#include "RGB_bar.h"
#include "ADC.h"
#include "DAC.h"


extern unsigned short ADC_DATA;

// function prototypes
void Hold_Blue_LED(void);
void Init_Timer3(uint32_t frequency);
void TIM3_IRQHandler(void);

void init_Timer1(void);

void Timer2_IRQHandler(void);

void Init_Timer2(void);

void Init_Timer5(void);
void TIM5_IRQHandler(void);

void interrupt_priority(void);

#endif