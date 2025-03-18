#ifndef timer
#define timer
#include <stm32f429xx.h>
#include "usart.h"
#include "LED.h"
#include "RGB_bar.h"
#include "ADC.h"
#include "DAC.h"

// function prototypes
void Set_Timer3_Frequency(uint32_t frequency);
void Init_Timer3(uint32_t frequency);
void Init_Timer5(void);
void float_to_string(float num, char *str);


// Timer interrupt service routines
void TIM2_IRQHandler(void);
void Init_Timer2(uint32_t frequency);
void Set_Timer2_Frequency(uint32_t frequency);  // Function to set the frequency of Timer 2
void TIM2_IRQHandler(void);            // Timer 2 interrupt handler (ISR)
void TIM3_IRQHandler(void);
void TIM5_IRQHandler(void);
void Hold_Blue_LED(void);
void Init_Timer5_PWM(void);

#endif