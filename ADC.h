#ifndef _ADC_H
#define _ADC_H// headder management
#include <stm32f4xx.h>// library





#define ADC_input_port		GPIOC // definitions
#define ADC_input_pin			0
#define ADC_Channel				10






void init_ADC(void);
unsigned short read_adc(void); // functiont prototypes
#endif 
