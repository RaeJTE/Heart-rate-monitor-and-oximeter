#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
													//this file contains the definitions for register addresses and values etc...
#include "PLL_Config.c"

void delay (void)
{	
	volatile unsigned int i;		//create variable
	for (i=0; i<1000000; i++);	//WAIT count to 1 million 
}

		//100ms BLOCKING DELAY
void delay_100ms_blocking(void)
{
	volatile unsigned int i;				//increment a variable to waste time
	for(i=0; i<SystemCoreClock/180; i++);		//incrementing a variable from 0 to 4,500,000 takes 100ms when MCU speed is 180MHz
}



void LED_INIT (void)
{
	//ENABLE PORT(S)
	//RCC->AHB1ENR |= 0x02;						//use label defined in stm32f4.h instead of hex value: easier to read and change
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	//ONLY GPIO B clock enable
	
	
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
	GPIOB->MODER |= 0x01;						//ONLY set  GPIOB0
	// the above assumes that bit 1 is to zero
	GPIOB->MODER &= ~0x02;					//ONLY clear GPIOB1
	
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED2
	GPIOB->MODER |= 0x0E;						//ONLY set  GPIOB14
	// the above assumes that bit 1 is to zero
	GPIOB->MODER &= ~0x0F;					//ONLY clear GPIOB15
	
	
	
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED3
	GPIOB->MODER |= 0x1C;						//ONLY set  GPIOB27
	// the above assumes that bit 1 is to zero
	GPIOB->MODER &= ~0x1D;					//ONLY clear GPIOB28
	
	
}	

void LED_ON (void)
{
			GPIOB->ODR |= 1;							//ONLY TURN LED ON

}

void LED_OFF (void)
{
			GPIOB->ODR &= ~1;		//ONLY TURN LED ON

}

int main(void)					// MAIN PROGRAM
{
	PLL_Config();										// Setup Internal Clock Speed to 180MHz
	SystemCoreClockUpdate();
	LED_INIT();

	//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
	while(1)		
	{
		LED_ON();											//ONLY TURN LED ON
		delay_100ms_blocking();				// 100ms DELAY
		LED_OFF();										//ONLY TURN LED OFF
		delay_100ms_blocking();				// 100ms DELAY
	}
}
