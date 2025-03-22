#ifndef timer
#define timer
#include <stm32f429xx.h>
#include "usart.h"
#include "LED.h"
#include "RGB_bar.h"
#include "ADC.h"
#include "DAC.h"

#define samplingRate 1000

// function prototypes
void float_to_string(float num, char *str);


// Timer interrupt service routines
void TIM2_IRQHandler(void);

void Init_Timer2(uint32_t frequency);
void TIM2_IRQHandler(void);            // Timer 2 interrupt handler (ISR)

void Init_Timer3(void);
void TIM3_IRQHandler(void);
void TIM3Delay (float usDelay);

void Init_Timer4(uint32_t frequency);
void TIM4_IRQHandler(void);

void interrupt_priority(void);

#endif