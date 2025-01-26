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
	PORT->MODER |= (0UL << (2*BIT));		//Set BIT to input mode
	PORT->OSPEEDR |= (0UL << (2*BIT));	//Make BIT Speed 2Mhz to save power
	PORT->PUPDR |= (3UL <<(2*BIT));			// Turn off Pullup and Pull down resistors for BIT
}

void FOUR_BTN_INIT(GPIO_TypeDef *PORT, unsigned int BIT0, unsigned int BIT1, unsigned int BIT2, unsigned int BIT3)
{
	FOUR_BTN_PORT_ENABLE();	//Activates the port for the four directional buttons
	//Sets the pins for the four buttons to be inputs
	set_BTN_input(BIT0);
	set_BTN_input(BIT1);
	set_BTN_input(BIT2);
	set_BTN_input(BIT3);
	//Sets the pins for the four buttons to be low speed to conserve power
	set_BTN_lowspeed(BIT0);
	set_BTN_lowspeed(BIT1);
	set_BTN_lowspeed(BIT2);
	set_BTN_lowspeed(BIT3);
	//Sets the pins for the four buttons to not use internal pull-up or pull-down resistors
	set_BTN_not_pull_up(BIT0);
	set_BTN_not_pull_up(BIT1);
	set_BTN_not_pull_up(BIT2);
	set_BTN_not_pull_up(BIT3);
}

void Toggle_LED(void)
{
	GPIOB->ODR^=(0b00000001<<LED_GRN);								//Toggles green LED
}

int readBTNValue(GPIO_TypeDef *PORT, unsigned int BIT) //Reads whether a given button is being pressed - made easier by the 4 buttons using pins 0,1,2,3
{	
	int value = PORT->IDR;	//Check pages 23 and 31 of GPIO lecture notes
	value &= (1<<BIT);
	return value;
}

