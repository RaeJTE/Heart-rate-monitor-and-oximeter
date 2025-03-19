#ifndef _ADC_H
#define _ADC_H
#include <stm32f4xx.h>

#define PCB_ADC_input_port		GPIOA
#define PCB_ADC_input_pin			7
#define NucleoADC_input_port		GPIOC
#define NucleoADC_input_pin			0
#define ADC_Channel				10

void init_ADC(void);
unsigned short read_adc(void);
#endif 
