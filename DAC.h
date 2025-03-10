#include <stm32f4xx.h>

#ifndef _DAC_H
#define _DAC_H

#define DAC_port	GPIOA
#define DAC1_pin		4
#define DAC2_pin		5

void init_DAC(void);
void output_dac1(unsigned short d);	//Max output at 65535	-	IR LED
void output_dac2(unsigned short d);	//Max output at 65535	- RED LED

#endif

