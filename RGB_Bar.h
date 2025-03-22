#include <stm32f4xx.h>
#include "ADC.h"
#include "DAC.h"
#include "usart.h"
#ifndef RGB_BAR_H


#define RGB_BAR_H


void init_GPIO_RGB_Bar(void);
void control_RGB_Bar(unsigned short adc_value);
void init_ADC_PA0(void);
unsigned short read_ADC_PA0(void);
void init_DAC2(void);
void output_DAC2(unsigned short value);

void RGB_main (void);

void output_DAC2(unsigned short value);
void turn_off_RGB_Bar(void);

void USART_Vout(unsigned short ADC_DATA, unsigned int int_part, unsigned int frac_part);


//unsigned int int_part;
//unsigned int frac_part;

void USART_Vsend ();

void bar_graph(unsigned int int_part, unsigned int frac_part);

#endif