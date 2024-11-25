#include <stm32f429xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
													//this file contains the definitions for register addresses and values etc...


int main(void)					// MAIN PROGRAM
{
	volatile unsigned int i;		//create variable
	
	//ENABLE PORT(S)
	RCC->AHB1ENR |= 0x02;						//ONLY GPIO B clock enable
	
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
	GPIOB->MODER |= 0x01;						//ONLY set new pin functions on GPIOB0

	//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
	while(1)		
	{
		GPIOB->ODR |= 1;							//ONLY TURN LED ON
		for (i=0; i<1000; i++);		//WAIT count to 1 million 
		GPIOB->ODR &= ~1;							//ONLY TURN LED OFF
		for (i=0; i<1000000; i++);		//WAIT by count to 1 million 
	}
}
