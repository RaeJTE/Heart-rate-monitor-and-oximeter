#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
													//this file contains the definitions for register addresses and values etc...
#include "PLL_Config.c"
#define LED_PORT	GPIOB			// Green LED on GPIOB
#define GREEN	0
#define BLUE	7
#define RED 14
#define LED	GREEN								// Green LED on Bit0
#define LEDon(PORT, BIT)   ((PORT->ODR) |= (1U << BIT))		// Macro to set port bit
#define LEDoff(PORT, BIT)   ((PORT->ODR) &= ~(1U << (BIT))) // Macro to clear port bit
																														//# change Macros to use BSRR

void delay (void)
{	
	volatile unsigned int i;		//create variable
	for (i=0; i<1000000; i++);		//WAIT count to 1 million 
}

		//100ms BLOCKING DELAY
void delay_100ms_blocking(void)
{
	volatile unsigned int i;				//increment a variable to waste time
	for(i=0; i<SystemCoreClock/180; i++);		//incrementing a variable from 0 to 4,500,000 takes 100ms when MCU speed is 180MHz
}

void LED_INIT (GPIO_TypeDef *PORT, unsigned int BIT)
{
	//ENABLE PORT(S)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	//ONLY GPIO B clock enable
	
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
	PORT->MODER &= ~(3UL << (2*BIT));		//Clear GPIOB1 & GPIOB0 - default INPUT state
	PORT->MODER |= (1UL << (2*BIT));			//ONLY set  GPIOB0 make Bit0 OUTPUT
	PORT->OTYPER &= ~(1UL << BIT);				// Make Bit0 output PUSH-PULL
	PORT->OSPEEDR &= ~(3UL << (2*BIT));	//Make Bit0 Speed 2Mhz to save power
	PORT->PUPDR &= ~(3UL <<(2*BIT));			// Turn off Pullup and Pull down resistors for Bit0
}	

void LED_ON (void)
{
			GPIOB->ODR |= (1UL<<LED);							//ONLY TURN LED on Bit0 ON
}

void LED_OFF (void)
{
			GPIOB->ODR &= ~(1UL<<LED);						//ONLY TURN LED on Bit0 ON
}


int main(void)										// MAIN PROGRAM
{
	PLL_Config();										// Setup Internal Clock Speed to 180MHz
	SystemCoreClockUpdate();
	LED_INIT(LED_PORT, LED);

	//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
	while(1)		
	{
		LEDon (LED_PORT, LED);				//Uses MACRO to Turn LED on										
		delay_100ms_blocking();				// 100ms DELAY
		
		LEDoff (LED_PORT, LED);				//Uses MACRO to Turn LED off
		delay_100ms_blocking();				// 100ms DELAY
	}
}
