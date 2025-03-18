#include <stdio.h>
#include "DAC.h"

void init_DAC(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
	DAC_port->MODER|=(3u<<(2*DAC1_pin));			//DAC1 output pin set as anaglogue
	DAC_port->MODER|=(3u<<(2*DAC2_pin));			//DAC2 output pin set as anaglogue
	
	RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
	DAC->CR|=DAC_CR_EN1;										//DAC1 enabled
	DAC->CR|=DAC_CR_EN2;										//DAC2 enabled
	
	DAC->DHR12R1 = 0;	//Defaults to DAC 1 outputting nothing
	DAC->DHR12R2 = 0;	//Defaults to DAC 2 outputting nothing
}

void output_dac1(unsigned short d)	//Max output at 65535
{
	DAC->DHR12R1=d;			//write data byte to DAC 1 output register
}

void output_dac2(unsigned short d)	//Max output at 65535
{
	DAC->DHR12R2=d;			//write data byte to DAC 2 output register
}

