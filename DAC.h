#include <stm32f4xx.h>

#ifndef _DAC_H_	//Ensures no double definition of _LCD_H_
#define _DAC_H_

#define DAC_port	GPIOA	//Defines which port is used for the DACs
#define DAC1_pin		4	//Defines which pin is used for the DAC1
#define DAC2_pin		5	//Defines which pin is used for the DAC2

void init_DAC(void);	//Initialises the DAC
void output_dac1(unsigned short d);	//Outputs DAC1 signal
void output_dac2(unsigned short d);	//Outputs DAC2 signal




#endif
