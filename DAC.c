#include <stdio.h>
#include "DAC.h"

void init_DAC(void)	//Initialises DAC
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;			//DAC port clock enable
	DAC_port->MODER|=(3u<<(2*DAC1_pin));		//DAC1 output pin set as anaglogue
	DAC_port->MODER|=(3u<<(2*DAC2_pin));		//DAC2 output pin set as anaglogue
	
	RCC->APB1ENR|=RCC_APB1ENR_DACEN;				//DAC clock enable
	DAC->CR|=DAC_CR_EN2;										//DAC enabled
}

void output_dac1(unsigned short d)	//Outputs DAC signal
{
	DAC->DHR12R2=d;			//write data byte to DAC 1 output register
}

void output_dac2(unsigned short d)	//Outputs DAC signal
{
	DAC->DHR12R2=d;			//write data byte to DAC 2 output register
}



