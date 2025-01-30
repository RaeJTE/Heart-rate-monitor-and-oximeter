#include <stm32f4xx.h>
#include "Buzz.h"
#include "LCD.h"


int melody[] = {1,2};



void initBuzz(void)
{
	//ENABLE PORT
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	//ONLY GPIO B clock enable
	
	//CONFIGURE PORT:GPIOB  PIN:13 TO OUTPUT for Buzzer
	BUZZ_PORT->MODER &= ~(3UL << (2*BUZZ_PIN));			//Clear GPIOB1 & GPIOB0 - default INPUT state
	BUZZ_PORT->MODER |= (1UL << (2*BUZZ_PIN));			//ONLY set  GPIOB0 make Bit13 OUTPUT
	BUZZ_PORT->OTYPER &= ~(1UL << BUZZ_PIN);				// Make Bit13 output PUSH-PULL
	BUZZ_PORT->OSPEEDR &= ~(3UL << (2*BUZZ_PIN));		//Make Bit13 Speed 2Mhz to save power
	BUZZ_PORT->PUPDR &= ~(3UL <<(2*BUZZ_PIN));			// Turn off Pullup and Pull down resistors for Bit13
}

void endlessBuzz(void)
{
	while(1)
	{
		BUZZ_PORT->ODR^=(0b00000001<<BUZZ_PIN);	//Toggles buzzer
		lcd_delayus(1000);
	}
}

void tempBuzz(int time_ms, int freq_Hz)	//Actual timings very approximate for now until incorporation of proper timers
{
	int i =0;
	int period_us = 1000000/freq_Hz;
	while(i<(100*time_ms/period_us))
	{
		BUZZ_PORT->ODR^=(0b00000001<<BUZZ_PIN);	//Toggles buzzer
		lcd_delayus(1/period_us);
		i++;
	}
}

