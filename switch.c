#include "switch.h"

void LED_INIT(GPIO_TypeDef *PORT, unsigned int BIT)
{
	//ENABLE PORT
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	//ONLY GPIO B clock enable
	
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
	PORT->MODER &= ~(3UL << (2*BIT));		//Clear GPIOB1 & GPIOB0 - default INPUT state
	PORT->MODER |= (1UL << (2*BIT));			//ONLY set  GPIOB0 make Bit0 OUTPUT
	PORT->OTYPER &= ~(1UL << BIT);				// Make Bit0 output PUSH-PULL
	PORT->OSPEEDR &= ~(3UL << (2*BIT));	//Make Bit0 Speed 2Mhz to save power
	PORT->PUPDR &= ~(3UL <<(2*BIT));			// Turn off Pullup and Pull down resistors for Bit0
}

void BLU_BTN_INIT(GPIO_TypeDef *PORT, unsigned int BIT)
{
	//Enable port
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	
	//Configure port
	PORT->MODER |= (0UL << (2*BIT));		//Set BIT to output mode
	PORT->OSPEEDR |= (0UL << (2*BIT));	//Make BIT Speed 2Mhz to save power
	PORT->PUPDR |= (3UL <<(2*BIT));			// Turn off Pullup and Pull down resistors for BIT
}

void Toggle_LED(void)
{
	GPIOB->ODR^=(0b00000001<<LED_GRN);								//Toggles green LED
}

void switchInit(void)
{
	switch_PORT_ENABLE();	//Clocks the port being used for inputs to enable it
	//Button 0
	set_BTN_input(BTN0_PIN);	//Sets to input mode
	set_BTN_lowspeed(BTN0_PIN);	//Sets to 2MHz (low speed) operation to save power
	set_BTN_pull_up(BTN0_PIN);	//Sets to pull up configuration
	//Button 1
	set_BTN_input(BTN1_PIN);	//Sets to input mode
	set_BTN_lowspeed(BTN1_PIN);	//Sets to 2MHz (low speed) operation to save power
	set_BTN_pull_up(BTN1_PIN);	//Sets to pull up configuration
	//Button 2
	set_BTN_input(BTN2_PIN);	//Sets to input mode
	set_BTN_lowspeed(BTN2_PIN);	//Sets to 2MHz (low speed) operation to save power
	set_BTN_pull_up(BTN2_PIN);	//Sets to pull up configuration
	//Button 3
	set_BTN_input(BTN3_PIN);	//Sets to input mode
	set_BTN_lowspeed(BTN3_PIN);	//Sets to 2MHz (low speed) operation to save power
	set_BTN_pull_up(BTN3_PIN);	//Sets to pull up configuration
}

int readBTNValue(GPIO_TypeDef *PORT, unsigned int BIT) //Reads whether a given button is being pressed - made easier by the 4 buttons using pins 0,1,2,3
{	
	int value = PORT->IDR;	//Check pages 23 and 31 of GPIO lecture notes
	value &= (1<<BIT);
	return value;
}

